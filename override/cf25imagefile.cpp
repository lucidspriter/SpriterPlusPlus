#include "cf25imagefile.h"

#include "spriterengine/global/settings.h"

#include "spriterengine/objectinfo/universalobjectinterface.h"

namespace SpriterEngine
{

	Cf25ImageFile::Cf25ImageFile(std::string initialFilePath, point initialDefaultPivot, LPRDATA rdPtr, Extension *ext) :
		ImageFile(initialFilePath,initialDefaultPivot),
		rdPtr(rdPtr), ext(ext)
	{
	}

	void Cf25ImageFile::renderSprite(UniversalObjectInterface * spriteInfo)
	{
		//if not loaded yet and sprite source is not empty and the corresponding sprite exists, load the sprite
		if (ext->SpriteSource.size()>0 && ext->SpriteSource.count(path()) && !ext->SpriteSource[path()].loaded)
		{
			cSurface source;
			//if the sprite from the active object is available and exists, clone it and release active object sprite
			if (LockImageSurface(ext->SpriteSource[path()].pObj->roHo.hoAdRunHeader->rhIdAppli, ext->SpriteSource[path()].imageNumber, source))
			{
				sprite.Clone(source);
				ext->SpriteSource[path()].loaded = true;
				UnlockImageSurface(source);
			}
		}

		int w = sprite.GetWidth();
		int h = sprite.GetHeight();
		float posX = spriteInfo->getPivot().x*w;
		float posY = spriteInfo->getPivot().y*h;
		POINT center = { (LONG)posX, (LONG)posY };
		// DWORD flags = STRF_RESAMPLE;// | STRF_RESAMPLE_TRANSP;// 0UL;
		DWORD flags = rdPtr->rs->rsEffect & EFFECTFLAG_ANTIALIAS ? (STRF_RESAMPLE_TRANSP) : 0UL;
		LPSURFACE psw = WinGetSurface((int)rdPtr->rHo.hoAdRunHeader->rhIdEditWin);
		sprite.BlitEx(*psw, spriteInfo->getPosition().x, spriteInfo->getPosition().y,
			spriteInfo->getScale().x, spriteInfo->getScale().y, 0, 0,
			w, h, &center, (float)toDegrees(spriteInfo->getAngle()),
			(rdPtr->rs->rsEffect & EFFECTFLAG_TRANSPARENT) ? BMODE_TRANSP : BMODE_OPAQUE,
			BlitOp(rdPtr->rs->rsEffect & EFFECT_MASK),
			rdPtr->rs->rsEffectParam, flags);
		
		//calculate collision rectangle
		RECT minR = { 0, 0, 0, 0 };
		POINT inPoints[4];
		POINT outPoints[4];
		inPoints[0] = { -center.x, -center.y };
		inPoints[1] = { -center.x, (1 - spriteInfo->getPivot().y)*h };
		inPoints[2] = { (1 - spriteInfo->getPivot().x)*w, -center.y };
		inPoints[3] = { (1 - spriteInfo->getPivot().x)*w, (1 - spriteInfo->getPivot().y)*h };
		for (int i = 0; i < 4; i++)
		{
			outPoints[i].x = (inPoints[i].x* spriteInfo->getScale().x * std::cos(spriteInfo->getAngle())) + (inPoints[i].y * spriteInfo->getScale().y * std::sin(spriteInfo->getAngle()));
			outPoints[i].y = (-inPoints[i].x * spriteInfo->getScale().x * std::sin(spriteInfo->getAngle())) + (inPoints[i].y * spriteInfo->getScale().y * std::cos(spriteInfo->getAngle()));
			outPoints[i].x += spriteInfo->getPosition().x;
			outPoints[i].y += spriteInfo->getPosition().y;
		}
		minR.left = min(min(min(outPoints[0].x, outPoints[1].x), outPoints[2].x), outPoints[3].x);
		minR.right = max(max(max(outPoints[0].x, outPoints[1].x), outPoints[2].x), outPoints[3].x);
		minR.top = min(min(min(outPoints[0].y, outPoints[1].y), outPoints[2].y), outPoints[3].y);
		minR.bottom = max(max(max(outPoints[0].y, outPoints[1].y), outPoints[2].y), outPoints[3].y);
		ext->displayRect.left = min(ext->displayRect.left, minR.left);
		ext->displayRect.right = max(ext->displayRect.right, minR.right);
		ext->displayRect.bottom = max(ext->displayRect.bottom, minR.bottom);
		ext->displayRect.top = min(ext->displayRect.top, minR.top);
	}
}
