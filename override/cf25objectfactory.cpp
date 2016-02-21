#include "cf25objectfactory.h"

#include "cf25pointinstanceinfo.h"
#include "cf25boxinstanceinfo.h"
#include "cf25boneinstanceinfo.h"
#include "cf25soundobjectinforeference.h"

#include "cf25triggerobjectinfo.h"

namespace SpriterEngine
{

	Cf25ObjectFactory::Cf25ObjectFactory(LPRDATA rdPtr, Extension *ext) :
		rdPtr(rdPtr), ext(ext)
	{
	}

	PointInstanceInfo * Cf25ObjectFactory::newPointInstanceInfo()
	{
		return new Cf25PointInstanceInfo(rdPtr);
	}

	BoxInstanceInfo * Cf25ObjectFactory::newBoxInstanceInfo(point size)
	{
		return new Cf25BoxInstanceInfo(size, rdPtr, ext);
	}

	BoneInstanceInfo * Cf25ObjectFactory::newBoneInstanceInfo(point size)
	{
		return new Cf25BoneInstanceInfo(size, rdPtr);
	}

	TriggerObjectInfo *Cf25ObjectFactory::newTriggerObjectInfo(std::string triggerName) 
	{
		return new Cf25TriggerObjectInfo(triggerName, ext);
	}
}