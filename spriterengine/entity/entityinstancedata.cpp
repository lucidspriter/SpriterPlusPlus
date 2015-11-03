#include "entityinstancedata.h"

#include "../objectref/transformprocessor.h"
#include "../objectinfo/tagobjectinforeference.h"
#include "../objectinfo/triggerobjectinfo.h"

#include "../override/soundobjectinforeference.h"
#include "../override/soundfile.h"

#include "../variable/variable.h"

#include "entityinstance.h"
#include "entity.h"


namespace SpriterEngine
{

	EntityInstanceData::EntityInstanceData(SpriterModel *model, EntityInstance *entityInstance, Entity *entity, ObjectFactory *objectFactory)
	{
		transformers.insert(std::make_pair(THIS_ENTITY, TransformProcessor(entityInstance)));
		entity->setupInstance(model, entityInstance, this, objectFactory);
	}

	UniversalObjectInterface *EntityInstanceData::getObjectInstance(int objectId)
	{
		auto& it = objects.find(objectId);
		if (it != objects.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getObjectInstance(std::string objectName)
	{
		auto& it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	TransformProcessor *EntityInstanceData::getTransformer(int id)
	{
		auto&  it = transformers.find(id);
		if (it != transformers.end())
		{
			return &(*it).second;
		}
		else
		{
			UniversalObjectInterface *object = getObjectInstance(id);
			if (object)
			{
				return &(*transformers.insert(std::make_pair(id, TransformProcessor(object))).first).second;
			}
			else
			{
				// error
				return 0;
			}
		}
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariables()
	{
		return getVariables(THIS_ENTITY);
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(int variableId)
	{
		return getVariable(THIS_ENTITY, variableId);
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariables(int objectId)
	{
		auto& it = variables.find(objectId);
		if (it != variables.end())
		{
			return &(*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(int objectId, int variableId)
	{
		VariableInstanceNameAndIdMap *variableMap = getVariables(objectId);
		if (variableMap)
		{
			return variableMap->getVariable(variableId);
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(std::string variableName)
	{
		return getVariable("", variableName);
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariables(std::string objectName)
	{
		auto&  it = variableObjectNameMap.find(objectName);
		if (it != variableObjectNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getVariable(std::string objectName, std::string variableName)
	{
		VariableInstanceNameAndIdMap *variableMap = getVariables(objectName);
		if (variableMap)
		{
			return variableMap->getVariable(variableName);
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getTags() const
	{
		return getTags("");
	}

	UniversalObjectInterface *EntityInstanceData::getTags(int objectId) const
	{
		auto& it = tags.find(objectId);
		if (it != tags.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	bool EntityInstanceData::tagIsActive(int objectId, std::string tagToCheck) const
	{
		UniversalObjectInterface *tagList = getTags(objectId);
		if (tagList)
		{
			return tagList->tagIsActive(tagToCheck);
		}
		else
		{
			// error
			return 0;
		}
	}

	bool EntityInstanceData::tagIsActive(std::string tagToCheck) const
	{
		return tagIsActive("", tagToCheck);
	}

	UniversalObjectInterface *EntityInstanceData::getTags(std::string objectName) const
	{
		auto& it = tagObjectNameMap.find(objectName);
		if (it != tagObjectNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	bool EntityInstanceData::tagIsActive(std::string objectName, std::string tagToCheck) const
	{
		UniversalObjectInterface *tagList = getTags(objectName);
		if (tagList)
		{
			return tagList->tagIsActive(tagToCheck);
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getTriggerObject(int triggerId)
	{
		auto& it = triggers.find(triggerId);
		if (it != triggers.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getTriggerObject(std::string triggerName)
	{
		auto& it = triggerNameMap.find(triggerName);
		if (it != triggerNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getSoundObject(int soundId)
	{
		auto& it = sounds.find(soundId);
		if (it != sounds.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *EntityInstanceData::getSoundObject(std::string soundName)
	{
		auto& it = soundNameMap.find(soundName);
		if (it != soundNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	void EntityInstanceData::setCurrentAnimation(int newAnimationIndex, AnimationInstance **currentAnimation)
	{
		if (newAnimationIndex < animations.size())
		{
			*currentAnimation = animations.at(newAnimationIndex);
		}
		else
		{
			// error
		}
	}

	void EntityInstanceData::setCurrentAnimation(const std::string & animationName, AnimationInstance **currentAnimation)
	{
		auto& it = animationNameMap.find(animationName);
		if (it != animationNameMap.end())
		{
			*currentAnimation = (*it).second;
		}
		else
		{
			// error
		}
	}


	void EntityInstanceData::pushBackAnimationInstance(std::string name, AnimationInstance * newAnimationInstance)
	{
		animations.push_back(newAnimationInstance);
		animationNameMap[name] = animations.back();
	}

	void EntityInstanceData::setObjectInstance(int id, std::string name, UniversalObjectInterface * newObjectInstance)
	{
		objectNameMap[name] = (*objects.insert(std::make_pair(id, newObjectInstance)).first).second;
	}

	VariableInstanceNameAndIdMap *EntityInstanceData::getVariableInstanceMap(int objectId, std::string objectName)
	{
		return variableObjectNameMap[objectName] = &variables[objectId];
	}

	void EntityInstanceData::setTagInstance(int objectId, std::string objectName)
	{
		tagObjectNameMap[objectName] = (*tags.insert(std::make_pair(objectId, new TagObjectInfoReference())).first).second;
	}

	void EntityInstanceData::setSoundInstance(int id, std::string name, FileReference * soundRef)
	{
		SoundFile *soundFile = soundRef->sound();
		if (soundFile)
		{
			soundNameMap[name] = (*sounds.insert(std::make_pair(id, soundFile->newSoundInfoReference())).first).second;
		}
	}

	void EntityInstanceData::setTriggerInstance(int id, std::string name, TriggerObjectInfo *newCustomTriggerObject)
	{
		TriggerObjectInfo *newTriggerObject = newCustomTriggerObject;
		if (!newTriggerObject)
		{
			newTriggerObject = new TriggerObjectInfo();
		}
		triggerNameMap[name] = (*triggers.insert(std::make_pair(id, newTriggerObject)).first).second;
	}

	AnimationInstance * EntityInstanceData::getAnimation(int animationIndex)
	{
		if (animationIndex < animations.size())
		{
			return animations.at(animationIndex);
		}
		else
		{
			// error
			return 0;
		}
	}

	void EntityInstanceData::playSoundTriggers()
	{
		for (auto& it : sounds)
		{
			it.second->playTrigger();
		}
	}

	void EntityInstanceData::playEventTriggers()
	{
		for (auto& it : triggers)
		{
			it.second->playTrigger();
		}
	}

}