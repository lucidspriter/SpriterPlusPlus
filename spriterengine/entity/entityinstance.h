#ifndef ENTITYINSTANCE_H
#define ENTITYINSTANCE_H

#include <map>
#include <vector>
#include <list>

#include "../animation/animationinstance.h"
#include "../objectref/transformprocessor.h"
#include "../file/filereference.h"
#include "../objectinfo/entityobjectinfo.h"
#include "../variable/variableinstancenameandidmap.h"

#include "entityinstancedata.h"

namespace SpriterEngine
{

	class Entity;
	class SpriterModel;
	class CharacterMapInterface;
	class ObjectFactory;

	typedef std::map<int, EntityInstanceData*> EntityInstanceDataMap;
	typedef std::vector<FileReference*> FileReferenceVector;
	typedef std::list<std::string> StringList;

	class EntityInstance : public UniversalObjectInterface
	{
	public:
		EntityInstance();
		EntityInstance(SpriterModel *model, Entity *entity, CharacterMapInterface *initialCharacterMapInterface, ObjectFactory *objectFactory);
		~EntityInstance();

		void setTimeElapsed(real timeElapsed);

		void startResumePlayback();
		void pausePlayback();

		void blend(real blendRatio, real timeRatio);

		void reprocessCurrentTime() override;


		UniversalObjectInterface *getObjectInstance(int objectId);
		UniversalObjectInterface * getObjectInstance(std::string objectName);
		FileReference *getFile(int fileId);

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		real getAlpha() override;

		real getCurrentTime() override;
		real getTimeRatio() override;

		VariableInstanceNameAndIdMap *getVariables() override;
		UniversalObjectInterface *getVariable(int variableId);
		VariableInstanceNameAndIdMap *getVariables(int objectId);
		UniversalObjectInterface *getVariable(int objectId, int variableId);

		UniversalObjectInterface *getVariable(std::string variableName);
		VariableInstanceNameAndIdMap *getVariables(std::string objectName);
		UniversalObjectInterface *getVariable(std::string objectName, std::string variableName);

		virtual real getRealValue(std::string variableName);
		virtual int getIntValue(std::string variableName);
		virtual std::string getStringValue(std::string variableName);

		virtual real getRealValue(std::string objectName, std::string variableName);
		virtual int getIntValue(std::string objectName, std::string variableName);
		virtual std::string getStringValue(std::string objectName, std::string variableName);

		UniversalObjectInterface *getTags() const override;
		UniversalObjectInterface *getTags(int objectId) const;
		bool tagIsActive(int objectId, std::string tagToCheck) const;

		bool tagIsActive(std::string tagToCheck) const override;
		UniversalObjectInterface *getTags(std::string objectName) const;
		bool tagIsActive(std::string objectName, std::string tagToCheck) const;

		UniversalObjectInterface *getTriggerObject(int triggerId);
		UniversalObjectInterface *getTriggerObject(std::string triggerName);

		UniversalObjectInterface *getSoundObject(int soundId);
		UniversalObjectInterface *getSoundObject(std::string soundName);


		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;
		void setSpin(int newSpin) override;

		void setCurrentEntity(int newEntityIndex) override;
		void setCurrentEntity(EntityInstanceData *newCurrentEntity) override;
		void setCurrentAnimation(int newAnimationIndex) override;
		void setCurrentAnimation(const std::string &animationName);
		void setCurrentAnimation(const std::string &animationName, real blendTime);
		void setCurrentAnimation(AnimationInstance *newCurrentAnimation) override;
		void setCurrentTime(real newCurrentTime);
		void setTimeRatio(real newCurrentTimeRatio) override;

		void setPlaybackSpeedRatio(real newPlaybackSpeedRatio);

		void applyCharacterMap(std::string mapName);
		void removeCharacterMap(std::string mapName);
		void removeAllCharacterMaps();

		void render() override;

		void playAllTriggers();
		void playSoundTriggers();
		void playEventTriggers();
		
		ObjectInterfaceVector *getZOrder() override;

		void appendEntity(SpriterModel *model, Entity *entity, ObjectFactory *objectFactory);

		EntityInstanceData *getEntity(int entityId) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

	private:
		EntityInstanceDataMap entities;

		FileReferenceVector files;

		ObjectInterfaceVector *zOrder;

		point position;
		AngleInfo angle;
		point scale;
		real alpha;

		EntityInstanceData *currentEntity;
		AnimationInstance *currentAnimation;

		bool isPlaying;

		AnimationInstance *blendedAnimation;
		real blendTotalTime;
		real blendCurrentTime;

		CharacterMapInterface *characterMapInterface;

		StringList appliedCharacterMaps;

		real playbackSpeedRatio;
	};

}

#endif // ENTITYINSTANCE_H
