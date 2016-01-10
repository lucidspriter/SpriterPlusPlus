#ifndef CF25TRIGGEROBJECTINFO_H
#define CF25TRIGGEROBJECTINFO_H

#include "Common.h"

#include "spriterengine/objectinfo/triggerobjectinfo.h"

namespace SpriterEngine
{

	class Cf25TriggerObjectInfo : public TriggerObjectInfo
	{
	public:
		Cf25TriggerObjectInfo(const std::string& name, Extension* ext);

		void playTrigger() override;

	private:
		const std::string name;
		Extension* ext;
	};

}

#endif // CF25TRIGGEROBJECTINFO_H