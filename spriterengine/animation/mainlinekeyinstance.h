#ifndef MAINLINEKEYINSTANCE_H
#define MAINLINEKEYINSTANCE_H

#include <vector>
#include <map>

#include "../global/global.h"

#include "../objectref/transformprocessor.h"

namespace SpriterEngine
{

	class ObjectRefInstance;

	typedef std::vector<ObjectRefInstance*> RefInstanceVector;

	typedef std::vector<UniversalObjectInterface*> ObjectInterfaceVector;

	class EntityInstance;
	class EntityInstanceData;
	class MainlineKey;
	class TimeInfo;
	class MainlineKeyInstance
	{
	public:
		MainlineKeyInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, MainlineKey *mainlineKey);
		~MainlineKeyInstance();

		real process(real currentTime, ObjectInterfaceVector **instanceZOrder);

		real getTime();
		real getNextTime();
		bool timeInRange(real timeToCheck);

	private:
		RefInstanceVector refs;
		ObjectInterfaceVector zOrder;
		TimeInfo *timeInfo;
	};

}

#endif // MAINLINEKEYINSTANCE_H
