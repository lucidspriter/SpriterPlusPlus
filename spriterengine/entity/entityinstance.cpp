#include "entityinstance.h"

#include "../charactermap/charactermapinterface.h"
#include "../objectinfo/tagobjectinforeference.h"
#include "../objectinfo/triggerobjectinfo.h"

#include "../override/soundobjectinforeference.h"

#include "../model/spritermodel.h"

#include "entity.h"
#include "entityinstancedata.h"

namespace SpriterEngine
{
	EntityInstance::EntityInstance() :
		zOrder(0),
		position(0, 0),
		scale(1, 1),
		alpha(1),
		currentEntity(0),
		currentAnimation(0),
		characterMapInterface(0),
		playbackSpeedRatio(1)
	{
	}
	EntityInstance::EntityInstance(SpriterModel *model, Entity *entity, CharacterMapInterface *initialCharacterMapInterface, ObjectFactory *objectFactory) :
		zOrder(0),
		position(0, 0),
		scale(1, 1),
		alpha(1),
		currentEntity(0),
		currentAnimation(0),
		characterMapInterface(initialCharacterMapInterface),
		playbackSpeedRatio(1)
	{
		model->setupFileReferences(&files);
		currentEntity = (*entities.insert(std::make_pair(entity->getId(), new EntityInstanceData(model, this, entity, objectFactory))).first).second;
		entity->setupInstance(model, this, currentEntity, objectFactory);
		setCurrentAnimation(0);
	}

	EntityInstance::~EntityInstance()
	{
		for (auto& it : files)
		{
			delete it;
		}

		for (auto& it : entities)
		{
			delete it.second;
		}
	}

	void EntityInstance::setTimeElapsed(real timeElapsed)
	{
		if (currentAnimation)
		{
			timeElapsed *= playbackSpeedRatio;
			currentAnimation->findAndProcessKeys(getCurrentTime() + timeElapsed, timeElapsed >= 0, &zOrder);
		}
		else
		{
			// error
		}
	}

	void EntityInstance::reprocessCurrentTime()
	{
		currentAnimation->processCurrentKeys(currentAnimation->currentTime(), &zOrder);
	}

	UniversalObjectInterface *EntityInstance::getObjectInstance(int objectId)
	{
		return currentEntity->getObjectInstance(objectId);
	}

	UniversalObjectInterface *EntityInstance::getObjectInstance(std::string objectName)
	{
		return currentEntity->getObjectInstance(objectName);
	}



	FileReference *EntityInstance::getFile(int fileId)
	{
		if (fileId < files.size())
		{
			return files.at(fileId);
		}
		else
		{
			// error
			return 0;
		}
	}

	point EntityInstance::getPosition()
	{
		return position;
	}

	real EntityInstance::getAngle()
	{
		return angle.angle;
	}

	point EntityInstance::getScale()
	{
		return scale;
	}

	real EntityInstance::getAlpha()
	{
		return alpha;
	}

	real EntityInstance::getCurrentTime()
	{
		return currentAnimation->currentTime();
	}

	real EntityInstance::getTimeRatio()
	{
		return getCurrentTime() / currentAnimation->length();
	}

	VariableInstanceNameAndIdMap *EntityInstance::getVariables()
	{
		return getVariables(THIS_ENTITY);
	}

	UniversalObjectInterface *EntityInstance::getVariable(int variableId)
	{
		return getVariable(THIS_ENTITY, variableId);
	}

	VariableInstanceNameAndIdMap *EntityInstance::getVariables(int objectId)
	{
		return currentEntity->getVariables(objectId);
	}

	UniversalObjectInterface *EntityInstance::getVariable(int objectId, int variableId)
	{
		return currentEntity->getVariable(objectId, variableId);
	}

	UniversalObjectInterface *EntityInstance::getVariable(std::string variableName)
	{
		return currentEntity->getVariable(variableName);
	}

	VariableInstanceNameAndIdMap *EntityInstance::getVariables(std::string objectName)
	{
		return currentEntity->getVariables(objectName);
	}

	UniversalObjectInterface *EntityInstance::getVariable(std::string objectName, std::string variableName)
	{
		return currentEntity->getVariable(objectName, variableName);
	}

	UniversalObjectInterface *EntityInstance::getTags() const
	{
		return currentEntity->getTags();
	}

	UniversalObjectInterface *EntityInstance::getTags(int objectId) const
	{
		return currentEntity->getTags(objectId);
	}

	bool EntityInstance::tagIsActive(int objectId, std::string tagToCheck) const
	{
		return currentEntity->tagIsActive(objectId, tagToCheck);
	}

	bool EntityInstance::tagIsActive(std::string tagToCheck) const
	{
		return currentEntity->tagIsActive("", tagToCheck);
	}

	UniversalObjectInterface *EntityInstance::getTags(std::string objectName) const
	{
		return currentEntity->getTags(objectName);
	}

	bool EntityInstance::tagIsActive(std::string objectName, std::string tagToCheck) const
	{
		return currentEntity->tagIsActive(objectName, tagToCheck);
	}

	UniversalObjectInterface *EntityInstance::getTriggerObject(int triggerId)
	{
		return currentEntity->getTriggerObject(triggerId);
	}

	UniversalObjectInterface *EntityInstance::getTriggerObject(std::string triggerName)
	{
		return currentEntity->getTriggerObject(triggerName);
	}

	UniversalObjectInterface *EntityInstance::getSoundObject(int soundId)
	{
		return currentEntity->getSoundObject(soundId);
	}

	UniversalObjectInterface *EntityInstance::getSoundObject(std::string soundName)
	{
		return currentEntity->getSoundObject(soundName);
	}

	void EntityInstance::setPosition(const point &newPosition)
	{
		position = newPosition;
	}

	void EntityInstance::setAngle(real newAngle)
	{
		angle.angle = newAngle;
	}

	void EntityInstance::setScale(const point &newScale)
	{
		scale = newScale;
	}

	void EntityInstance::setAlpha(real newAlpha)
	{
		alpha = newAlpha;
	}

	void EntityInstance::setSpin(int newSpin)
	{
		angle.spinDirection = newSpin;
	}


	void EntityInstance::setCurrentEntity(int newEntityId)
	{
		auto it = entities.find(newEntityId);
		if (it != entities.end())
		{
			currentEntity = (*it).second;
		}
		else
		{
			// error
		}
	}

	void EntityInstance::setCurrentEntity(EntityInstanceData * newCurrentEntity)
	{
		currentEntity = newCurrentEntity;
	}

	void EntityInstance::setCurrentAnimation(int newAnimationIndex)
	{
		currentEntity->setCurrentAnimation(newAnimationIndex, &currentAnimation);
	}

	void EntityInstance::setCurrentAnimation(const std::string & animationName)
	{
		currentEntity->setCurrentAnimation(animationName, &currentAnimation);
	}

	void EntityInstance::setCurrentAnimation(AnimationInstance * newCurrentAnimation)
	{
		currentAnimation = newCurrentAnimation;
	}

	void EntityInstance::setCurrentTime(real newCurrentTime)
	{
		if (currentAnimation)
		{
			currentAnimation->findAndProcessKeys(newCurrentTime, newCurrentTime > getCurrentTime(), &zOrder);
		}
		else
		{
			// error
		}
	}

	void EntityInstance::setTimeRatio(real newCurrentTimeRatio)
	{
		currentAnimation->findCurrentKeys(newCurrentTimeRatio * currentAnimation->length(), newCurrentTimeRatio >= inverseLinear(0, currentAnimation->length(), getCurrentTime()));
	}

	void EntityInstance::setPlaybackSpeedRatio(real newPlaybackSpeedRatio)
	{
		playbackSpeedRatio = newPlaybackSpeedRatio;
	}

	void EntityInstance::applyCharacterMap(std::string mapName)
	{
		characterMapInterface->applyCharacterMap(mapName, &files);
		appliedCharacterMaps.push_back(mapName);
	}

	void EntityInstance::removeCharacterMap(std::string mapName)
	{
		characterMapInterface->removeAllCharacterMaps(&files);
		appliedCharacterMaps.remove(mapName);
		for (auto& it : appliedCharacterMaps)
		{
			characterMapInterface->applyCharacterMap(it, &files);
		}
	}

	void EntityInstance::removeAllCharacterMaps()
	{
		characterMapInterface->removeAllCharacterMaps(&files);
		appliedCharacterMaps.clear();
	}

	void EntityInstance::render()
	{
		for (auto& it : *zOrder)
		{
			it->render();
		}
	}

	void EntityInstance::playAllTriggers()
	{
		playSoundTriggers();
		playEventTriggers();
	}

	void EntityInstance::playSoundTriggers()
	{
		currentEntity->playSoundTriggers();
	}

	void EntityInstance::playEventTriggers()
	{
		currentEntity->playEventTriggers();
	}

	ObjectInterfaceVector * EntityInstance::getZOrder()
	{
		return zOrder;
	}

	void EntityInstance::appendEntity(SpriterModel * model, Entity * entity, ObjectFactory * objectFactory)
	{
		model->setupFileReferences(&files);
		EntityInstanceData *newEntityData = (*entities.insert(std::make_pair(entity->getId(), new EntityInstanceData(model, this, entity, objectFactory))).first).second;
		entity->setupInstance(model, this, newEntityData, objectFactory);
	}

	EntityInstanceData * EntityInstance::getEntity(int entityId)
	{
		auto it = entities.find(entityId);
		if (it != entities.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

}
