#include "objectrefinstance.h"

#include "../entity/entityinstance.h"
#include "../timeline/timelinekey.h"

#include "../objectinfo/universalobjectinterface.h"

#include "transformprocessor.h"

namespace SpriterEngine
{

	ObjectRefInstance::ObjectRefInstance(UniversalObjectInterface *initialResultObject,
		TransformProcessor *initialParentTransformer,
		TimelineKey *initialKey) :
		resultObjectInterface(initialResultObject),
		parentTransformer(initialParentTransformer),
		key(initialKey)
	{
	}

	void ObjectRefInstance::process(real currentTime)
	{
		key->process(currentTime, resultObjectInterface);
		if (parentTransformer)
		{
			parentTransformer->transformChildObject(resultObjectInterface);
		}
		else
		{
			// error
		}
	}

	UniversalObjectInterface *ObjectRefInstance::resultObject() const
	{
		return resultObjectInterface;
	}

}
