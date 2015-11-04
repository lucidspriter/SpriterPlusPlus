#include "spriteobjectinfo.h"

namespace SpriterEngine
{

	SpriteObjectInfo::SpriteObjectInfo() :
		scale(1, 1),
		alpha(1)
	{
	}

	point SpriteObjectInfo::getPosition()
	{
		return position;
	}

	real SpriteObjectInfo::getAngle()
	{
		return angle.angle;
	}

	point SpriteObjectInfo::getScale()
	{
		return scale;
	}

	real SpriteObjectInfo::getAlpha()
	{
		return alpha;
	}

	point SpriteObjectInfo::getPivot()
	{
		return pivot;
	}

	ImageFile *SpriteObjectInfo::getImage()
	{
		return imageFile;
	}


	void SpriteObjectInfo::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void SpriteObjectInfo::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void SpriteObjectInfo::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void SpriteObjectInfo::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void SpriteObjectInfo::setPivot(const point &newPivot)
	{
		pivot = newPivot;
	}

	void SpriteObjectInfo::setImage(ImageFile *newImageFile)
	{
		imageFile = newImageFile;
	}

	void SpriteObjectInfo::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}

	void SpriteObjectInfo::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setAngle(angle.angleLinear(bObject->getAngle(), t));
		resultObject->setPosition(linear(position, bObject->getPosition(), t));
		resultObject->setScale(linear(scale, bObject->getScale(), t));
		resultObject->setAlpha(linear(alpha, bObject->getAlpha(), t));
		resultObject->setPivot(pivot);
		resultObject->setImage(imageFile);
	}

	void SpriteObjectInfo::render()
	{
		if (imageFile)
		{
			imageFile->renderSprite(this);
		}
	}

}
