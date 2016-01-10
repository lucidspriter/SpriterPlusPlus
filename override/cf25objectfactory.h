#ifndef CF25OBJECTFACTORY_H
#define CF25OBJECTFACTORY_H

#include "Common.h"

#include "spriterengine/override/objectfactory.h"

namespace SpriterEngine
{

	class Cf25ObjectFactory : public ObjectFactory
	{
	public:
		Cf25ObjectFactory(LPRDATA rdPtr, Extension* ext);
		
		PointInstanceInfo *newPointInstanceInfo() override;

		BoxInstanceInfo *newBoxInstanceInfo(point size) override;

		BoneInstanceInfo *newBoneInstanceInfo(point size) override;

		TriggerObjectInfo *newTriggerObjectInfo(std::string triggerName) override;

	private:
		LPRDATA rdPtr;
		Extension *ext;
	};

}

#endif // CF25OBJECTFACTORY_H
