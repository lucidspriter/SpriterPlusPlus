#include "cf25boneinstanceinfo.h"

#include "spriterengine/global/settings.h"

namespace SpriterEngine
{

	Cf25BoneInstanceInfo::Cf25BoneInstanceInfo(point initialSize, LPRDATA rdPtr) :
		BoneInstanceInfo(initialSize),
		rdPtr(rdPtr)
	{
		pts[0] = { 0, initialSize.y / 2.0 };
		pts[1] = { 4, 0};
		pts[2] = { initialSize.x, initialSize.y / 2.0 };
		pts[3] = { 4, initialSize.y};
	}

	void Cf25BoneInstanceInfo::render()
	{
		if (Settings::renderDebugBones)
		{
			LPSURFACE psw = WinGetSurface((int)rdPtr->rHo.hoAdRunHeader->rhIdEditWin);
			POINT points[4];
			for (int i = 0; i < 4; i++)
			{
				// Left Handed rotation in CF2.5 (Direct3D convention)
				//p'x = (px-ox) * cos + (py-oy) * sin + ox
				//p'y = -(px-ox) * sin + (py-oy) * cos + oy
				points[i].x = pts[0].x + ((pts[i].x - pts[0].x) * getScale().x * std::cos(getAngle())) + ((pts[i].y - pts[0].y) * getScale().y * std::sin(getAngle()));
				points[i].y = pts[0].y + (-(pts[i].x - pts[0].x) * getScale().x * std::sin(getAngle())) + ((pts[i].y - pts[0].y) * getScale().y * std::cos(getAngle()));
				points[i].x += getPosition().x;
				points[i].y += getPosition().y;
			}
			psw->Line(points[0].x, points[0].y, points[1].x, points[1].y,2,GREEN);
			psw->Line(points[1].x, points[1].y, points[2].x, points[2].y, 2, GREEN);
			psw->Line(points[2].x, points[2].y, points[3].x, points[3].y, 2, GREEN);
			psw->Line(points[3].x, points[3].y, points[0].x, points[0].y, 2, GREEN);
		}
	}

}
