#ifndef ANIMATIONINSTANCE_H
#define ANIMATIONINSTANCE_H

#include <vector>

#include "mainlinekeyinstance.h"

namespace SpriterEngine
{

	class MainlineKeyInstance;
	class EntityInstanceData;
	class Animation;
	class TimelineInstance;

	typedef std::vector<MainlineKeyInstance*> MainlineKeyInstanceVector;
	typedef MainlineKeyInstanceVector::iterator MainlineKeyInstanceVectorIterator;
	typedef std::vector<TimelineInstance*>TimelineInstanceVector;
	
	class AnimationInstance
	{
	public:
		AnimationInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, Animation *animation);
		~AnimationInstance();

		void findAndProcessKeys(real newTime, bool forward, ObjectInterfaceVector ** instanceZOrder);

		void findCurrentKeys(real newTime, bool forward);
		void processCurrentKeys(real newTime, ObjectInterfaceVector **instanceZOrder);

		bool looping();

		real length();

		real currentTime();

		real processRefKeys(real newTime);
		void blendRefKeys(real newTime, real blendRatio);
		void setZOrder(ObjectInterfaceVector ** instanceZOrder);
		void processRefTransforms();

		void processCurrentTimelineKeys(real newTime);

		void blendCurrentTimelineKeys(real newTime, real blendRatio);

	private:
		void findCurrentTimelineKeys(real newTime, bool forward);

		void findCurrentMainlineKey(real newTime, bool forward);
		real processCurrentMainlineKey(real newTime, ObjectInterfaceVector **instanceZOrder);

		void findMainlineKeyTimeForward(real newTime);
		void findMainlineKeyTimeBackward(real newTime);

		real time;

		MainlineKeyInstanceVector mainlineKeys;
		MainlineKeyInstanceVectorIterator mainlineKeyIterator;

		TimelineInstanceVector timelines;

		real animationLength;
		bool isLooping;
	};

}

#endif // ANIMATIONINSTANCE_H
