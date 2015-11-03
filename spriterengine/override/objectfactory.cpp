#include "objectfactory.h"

#include "../objectinfo/pointobjectinfo.h"
#include "../objectinfo/boneinstanceinfo.h"
#include "../objectinfo/boxinstanceinfo.h"
#include "../objectinfo/triggerobjectinfo.h"

namespace SpriterEngine
{

	ObjectFactory::ObjectFactory()
	{
	}

	PointObjectInfo * ObjectFactory::newPointObjectInfo()
	{
		return new PointObjectInfo();
	}

	BoneInstanceInfo * ObjectFactory::newBoneInstanceInfo(point size)
	{
		return new BoneInstanceInfo(size);
	}

	BoxInstanceInfo * ObjectFactory::newBoxInstanceInfo(point size)
	{
		return new BoxInstanceInfo(size);
	}

	TriggerObjectInfo * ObjectFactory::newTriggerObjectInfo(std::string newTriggerName)
	{
		return new TriggerObjectInfo();
	}

}