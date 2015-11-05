#ifndef ENTITYINSTANCEDATA_H
#define ENTITYINSTANCEDATA_H

#include <vector>
#include <map>

#include "../objectinfo/universalobjectinterface.h"

#include "../variable/variableinstancenameandidmap.h"

namespace SpriterEngine
{
	class SpriterModel;
	class Entity;
	class ObjectFactory;
	class TransformProcessor;
	class AnimationInstance;
	class TagObjectInfoReference;
	class SoundObjectInfoReference;
	class TriggerObjectInfo;
	class FileReference;
	class EntityInstance;
	class Animation;

	typedef std::map<int, TransformProcessor> TransformProcessorMap;

	typedef std::vector<AnimationInstance*> AnimationInstanceIdMap;
	typedef std::map<std::string, AnimationInstance*> AnimationInstanceNameMap;

	typedef std::map<int, UniversalObjectInterface*> ObjectInterfaceIdMap;
	typedef std::map<std::string, UniversalObjectInterface*> ObjectInterfaceNameMap;

	typedef std::map<int, VariableInstanceNameAndIdMap> VariableInstanceObjectIdMap;
	typedef std::map<std::string, VariableInstanceNameAndIdMap*> VariableInstanceObjectNameMap;

	typedef std::map<int, TagObjectInfoReference*> TagIdMap;
	typedef std::map<std::string, TagObjectInfoReference*> TagNameMap;

	typedef std::map<int, SoundObjectInfoReference*> SoundIdMap;
	typedef std::map<std::string, SoundObjectInfoReference*> SoundNameMap;

	typedef std::map<int, TriggerObjectInfo*> TriggerIdMap;
	typedef std::map<std::string, TriggerObjectInfo*> TriggerNameMap;

	class EntityInstanceData : UniversalObjectInterface
	{
	public:
		EntityInstanceData(SpriterModel *model, EntityInstance *entityInstance, Entity *entity, ObjectFactory *objectFactory);
		
		UniversalObjectInterface *getObjectInstance(int objectId);
		UniversalObjectInterface * getObjectInstance(std::string objectName);

		TransformProcessor *getTransformer(int id);

		VariableInstanceNameAndIdMap *getVariables() override;
		UniversalObjectInterface *getVariable(int variableId);
		VariableInstanceNameAndIdMap *getVariables(int objectId);
		UniversalObjectInterface *getVariable(int objectId, int variableId);

		UniversalObjectInterface *getVariable(std::string variableName);
		VariableInstanceNameAndIdMap *getVariables(std::string objectName);
		UniversalObjectInterface *getVariable(std::string objectName, std::string variableName);

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

		void setCurrentAnimation(int newAnimationIndex, AnimationInstance **currentAnimation);
		void setCurrentAnimation(const std::string &animationName, AnimationInstance **currentAnimation);

		void pushBackAnimationInstance(std::string name, AnimationInstance *newAnimationInstance);
		void setObjectInstance(int id, std::string name, UniversalObjectInterface *newObjectInstance);
		VariableInstanceNameAndIdMap *getVariableInstanceMap(int objectId, std::string objectName);
		void setTagInstance(int objectId, std::string objectName);
		void setSoundInstance(int id, std::string name, FileReference * soundRef);
		void setTriggerInstance(int id, std::string name, TriggerObjectInfo *newCustomTriggerObject = 0);

		AnimationInstance *getAnimation(int animationIndex);

		void playSoundTriggers();
		void playEventTriggers();

	protected:
		AnimationInstanceIdMap animations;
		AnimationInstanceNameMap animationNameMap;

		ObjectInterfaceIdMap objects;
		ObjectInterfaceNameMap objectNameMap;

		TransformProcessorMap transformers;

		VariableInstanceObjectIdMap variables;
		VariableInstanceObjectNameMap variableObjectNameMap;

		TagIdMap tags;
		TagNameMap tagObjectNameMap;

		SoundIdMap sounds;
		SoundNameMap soundNameMap;

		TriggerIdMap triggers;
		TriggerNameMap triggerNameMap;
	};

}

#endif // ENTITYOBJECTINFO_H

