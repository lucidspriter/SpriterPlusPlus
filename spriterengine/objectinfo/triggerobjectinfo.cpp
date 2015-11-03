#include "triggerobjectinfo.h"

namespace SpriterEngine
{

	TriggerObjectInfo::TriggerObjectInfo() :
		triggerCount(0)
	{
	}

	int TriggerObjectInfo::getTriggerCount()
	{
		return triggerCount;
	}

	void TriggerObjectInfo::setTriggerCount(int newTriggerCount)
	{
		triggerCount = newTriggerCount;
	}

}
