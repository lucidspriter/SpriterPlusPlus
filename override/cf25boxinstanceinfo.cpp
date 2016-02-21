#include "cf25boxinstanceinfo.h"

#include "spriterengine/global/settings.h"

namespace SpriterEngine
{

	Cf25BoxInstanceInfo::Cf25BoxInstanceInfo(point initialSize, LPRDATA rdPtr, Extension * ext) :
		BoxInstanceInfo(initialSize),
		rdPtr(rdPtr), ext(ext)
	{
		int w = initialSize.x;
		int h = initialSize.y;
		float posX = getPivot().x*w;
		float posY = getPivot().y*h;
		POINT center = { (LONG)posX, (LONG)posY };
		pts[0] = { -center.x, -center.y };
		pts[1] = { -center.x, (1 - getPivot().y)*initialSize.y };
		pts[2] = { (1 - getPivot().x)*initialSize.x, -center.y };
		pts[3] = { (1 - getPivot().x)*initialSize.x, (1 - getPivot().y)*initialSize.y };
	}

	void Cf25BoxInstanceInfo::render()
	{
		if (Settings::renderDebugBoxes)
		{
			int w = getSize().x;
			int h = getSize().y;
			float posX = getPivot().x*w;
			float posY = getPivot().y*h;
			POINT center = { (LONG)posX, (LONG)posY };
			
			pts[0] = { -center.x, (1 - getPivot().y)*h };
			pts[1] = { (1 - getPivot().x)*w, (1 - getPivot().y)*h };
			pts[2] = { (1 - getPivot().x)*w, -center.y };
			pts[3] = { -center.x, -center.y };
			
			LPSURFACE psw = WinGetSurface((int)rdPtr->rHo.hoAdRunHeader->rhIdEditWin);
			POINT points[4];
			for (int i = 0; i < 4; i++)
			{
				// Left Handed rotation in CF2.5 (Direct3D convention)
				//p'x =  px * cos + py * sin
				//p'y = -px * sin + py * cos
				points[i].x =  pts[i].x * getScale().x * std::cos(getAngle()) + pts[i].y * getScale().y * std::sin(getAngle());
				points[i].y = -pts[i].x * getScale().x * std::sin(getAngle()) + pts[i].y * getScale().y * std::cos(getAngle());
				points[i].x += getPosition().x;
				points[i].y += getPosition().y;
			}
			psw->Line(points[0].x, points[0].y, points[1].x, points[1].y, 5, RED);
			psw->Line(points[1].x, points[1].y, points[2].x, points[2].y, 5, RED);
			psw->Line(points[2].x, points[2].y, points[3].x, points[3].y, 5, RED);
			psw->Line(points[3].x, points[3].y, points[0].x, points[0].y, 5, RED);
		}
	}

}
