#include "cf25triggerobjectinfo.h"

namespace SpriterEngine
{

	Cf25TriggerObjectInfo::Cf25TriggerObjectInfo(const std::string& name, Extension* ext) : name(name), ext(ext)
	{
	}


	void Cf25TriggerObjectInfo::playTrigger()
	{
		if (getTriggerCount())
		{
			ext->TriggerEvent[name] += 1;
		}
	}
}