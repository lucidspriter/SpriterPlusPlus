#include "objectref.h"

#include "../entity/entityinstance.h"

#include "objectrefinstance.h"

namespace SpriterEngine
{

	ObjectRef::ObjectRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey) :
		objectId(initialObjectId),
		parentObjectId(initialParentObjectId),
		key(initialKey)
	{
	}

	ObjectRefInstance *ObjectRef::getNewObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData)
	{
		UniversalObjectInterface *initialResultObject = entityInstanceData->getObjectInstance(objectId);
		if (!initialResultObject)
		{
			// error
			return 0;
		}
		TransformProcessor *initialParentTransformer = entityInstanceData->getTransformer(parentObjectId);
		if (!initialParentTransformer)
		{
			// error
			return 0;
		}
		return getNewSpecializedObjectRefInstance(entityInstance, entityInstanceData, initialParentTransformer, initialResultObject);
	}

	int ObjectRef::id()
	{
		return objectId;
	}

	TimelineKey * ObjectRef::getKey()
	{
		return key;
	}

	ObjectRefInstance *ObjectRef::getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance)
	{
		return new ObjectRefInstance(objectInstance, initialParentTransformer, getKey());
	}

}
