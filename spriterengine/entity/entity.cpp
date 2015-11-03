#include "entity.h"
#include "object.h"

#include "../animation/animationinstance.h"

#include "../override/objectfactory.h"
#include "../model/spritermodel.h"

#include "entityinstance.h"
#include "entityinstancedata.h"

namespace SpriterEngine
{

	Entity::Entity(std::string initialName, int initialId, FileVector *initialFileVector) :
		name(initialName),
		entityId(initialId),
		files(initialFileVector)
	{
	}

	int Entity::getId()
	{
		return entityId;
	}

	std::string Entity::getName()
	{
		return name;
	}

	EntityInstance *Entity::getNewEntityInstance(SpriterModel *model, ObjectFactory *objectFactory)
	{
		return new EntityInstance(model, this, this, objectFactory);
	}

	void Entity::setupInstance(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		setupObjectInstances(model, entityInstance, entityInstanceData, objectFactory);
		setupVariableInstances(entityInstanceData->getVariableInstanceMap(THIS_ENTITY, ""));
		entityInstanceData->setTagInstance(THIS_ENTITY, "");
		setupAnimationInstances(entityInstance, entityInstanceData);
	}

	Object *Entity::setObject(std::string objectName, Object::ObjectType objectType)
	{
		switch (objectType)
		{
		case Object::OBJECTTYPE_SOUND:
			return setSoundObject(objectName);

		case Object::OBJECTTYPE_TRIGGER:
			return setTriggerObject(objectName);

		case Object::OBJECTTYPE_ENTITY:
			return setSubEntityObject(objectName);

		default:
			return setSpatialObject(objectName, objectType);
		}

	}

	Object * Entity::getObject(int objectId)
	{
		auto& it = objectIdMap.find(objectId);
		if (it != objectIdMap.end())
		{
			return (*it).second;
		}
		else
		{
			// error
			return 0;
		}
	}

	Variable * Entity::getVariable(int objectId, int variableId)
	{
		if (objectId == THIS_ENTITY)
		{
			return VariableContainer::getVariable(variableId);
		}
		else
		{
			Object *object = getObject(objectId);
			if (object)
			{
				return object->getVariable(variableId);
			}
			else
			{
				// error
				return 0;
			}
		}
	}

	Object * Entity::setSpatialObject(std::string objectName, Object::ObjectType objectType)
	{
		auto& it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			return objectIdMap[objectNameMap.size()] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, objectNameMap.size(), objectType))).first).second);
		}
	}

	Object * Entity::setSoundObject(std::string objectName)
	{
		auto& it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			return soundIdMap[objectNameMap.size()] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, objectNameMap.size(), Object::OBJECTTYPE_SOUND))).first).second);
		}
	}

	Object * Entity::setTriggerObject(std::string objectName)
	{
		auto& it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			return triggerIdMap[objectNameMap.size()] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, objectNameMap.size(), Object::OBJECTTYPE_TRIGGER))).first).second);
		}
	}

	Object * Entity::setSubEntityObject(std::string objectName)
	{
		auto& it = objectNameMap.find(objectName);
		if (it != objectNameMap.end())
		{
			return &(*it).second;
		}
		else
		{
			return subEntityIdMap[objectNameMap.size()] = (&(*objectNameMap.insert(std::make_pair(objectName, Object(objectName, objectNameMap.size(), Object::OBJECTTYPE_ENTITY))).first).second);
		}
	}

	CharacterMap *Entity::addCharacterMap(std::string name)
	{
		return &characterMaps[name];
	}

	void Entity::applyCharacterMap(std::string mapName, FileReferenceVector *mappedFiles)
	{
		auto& it = characterMaps.find(mapName);
		if (it != characterMaps.end())
		{
			(*it).second.applyCharacterMap(mappedFiles);
		}
		else
		{
			// error
		}
	}

	void Entity::removeAllCharacterMaps(FileReferenceVector *mappedFiles)
	{
		auto& mappedFileIt = mappedFiles->begin();
		for (auto& it : *files)
		{
			(*mappedFileIt++)->setFile(it);
		}
	}

	Animation *Entity::pushBackAnimation(std::string animationName, real length, bool looping)
	{
		animations.push_back(new Animation(animationName, length, looping));
		return animations.back();
	}

	UniversalObjectInterface *Entity::getNewObjectInfoInstance(int objectId)
	{
		auto& it = objectIdMap.find(objectId);
		if (it != objectIdMap.end())
		{
			return (*it).second->getNewObjectInfoInstance();
		}
		else
		{
			// error
			return 0;
		}
	}

	void Entity::setupDefaultVariableTimelines()
	{
		for (auto& animIt : animations)
		{
			for (auto& objIt : objectNameMap)
			{
				objIt.second.setupDefaultVariableTimelines(animIt, objIt.second.getId());
			}
			VariableContainer::setupDefaultVariableTimelines(animIt, THIS_ENTITY);
		}
	}

	void Entity::setupAnimationInstances(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData)
	{
		for (auto& it : animations)
		{
			entityInstanceData->pushBackAnimationInstance(it->getName(), new AnimationInstance(entityInstance, entityInstanceData, it));
		}
	}

	void Entity::setupObjectInstance(Object *object, SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		object->addObjectInstanceToEntityInstanceData(model, entityInstance, entityInstanceData, objectFactory);
		object->setupVariableInstances(entityInstanceData->getVariableInstanceMap(object->getId(), object->getName()));
		entityInstanceData->setTagInstance(object->getId(), object->getName());
	}

	void Entity::setupObjectInstances(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory)
	{
		for (auto& it : objectNameMap)
		{
			setupObjectInstance(&it.second, model, entityInstance, entityInstanceData, objectFactory);
		}
	}

}
