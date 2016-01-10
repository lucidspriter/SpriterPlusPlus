#include "cf25pointinstanceinfo.h"

#include "spriterengine/global/settings.h"

namespace SpriterEngine
{

	Cf25PointInstanceInfo::Cf25PointInstanceInfo(LPRDATA rdPtr) :
		rdPtr(rdPtr)
	{
	}

	void Cf25PointInstanceInfo::render()
	{
		if (Settings::renderDebugPoints)
		{
			LPSURFACE psw = WinGetSurface((int)rdPtr->rHo.hoAdRunHeader->rhIdEditWin);
			psw->Rectangle(getPosition().x - 3, getPosition().y - 3, getPosition().x + 3, getPosition().y + 3, BLUE, 1, BLUE);
		}
	}

}
