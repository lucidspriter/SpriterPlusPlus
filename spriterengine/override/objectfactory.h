#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <string>

#include "../global/global.h"

namespace SpriterEngine
{

	class PointInstanceInfo;
	class BoneInstanceInfo;
	class BoxInstanceInfo;
	class TriggerObjectInfo;

	class ObjectFactory
	{
	public:
		ObjectFactory();
		
		// TODO: Override along with PointObjectInfo::render() to allow debug display of point objects;
		virtual PointInstanceInfo *newPointInstanceInfo();

		// TODO: Override along with BoneObjectInfo::render() to allow debug display of bone objects;
		virtual BoneInstanceInfo *newBoneInstanceInfo(point size);

		// TODO: Override along with BoxObjectInfo::render() to allow debug display of box objects;
		virtual BoxInstanceInfo *newBoxInstanceInfo(point size);

		// TODO: Override along with TriggerObjectInfo::playTrigger() to allow for triggering actions;
		virtual TriggerObjectInfo *newTriggerObjectInfo(std::string triggerName);
	};

}

#endif // OBJECTFACTORY_H
