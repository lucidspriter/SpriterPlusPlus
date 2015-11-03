#include "entityref.h"

#include "../entity/entityinstance.h"

#include "entityrefinstance.h"


namespace SpriterEngine
{

	EntityRef::EntityRef(int initialObjectId, int initialParentObjectId, TimelineKey *initialKey, int initialEntityId, int initialAnimationIndex) :
		ObjectRef(initialObjectId, initialParentObjectId, initialKey),
		entityId(initialEntityId),
		animationIndex(initialAnimationIndex)
	{
	}

	ObjectRefInstance *EntityRef::getNewSpecializedObjectRefInstance(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, TransformProcessor *initialParentTransformer, UniversalObjectInterface *objectInstance)
	{			
		EntityInstanceData *initialEntity = objectInstance->getEntity(entityId);
		if (!initialEntity)
		{
			// error
			return 0;
		}
		return new EntityRefInstance(objectInstance, initialParentTransformer, getKey(), initialEntity, initialEntity->getAnimation(animationIndex));
	}

}
