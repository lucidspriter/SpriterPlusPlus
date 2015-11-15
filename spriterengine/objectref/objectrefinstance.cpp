#include "objectrefinstance.h"

#include "../global/settings.h"

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
		processKey(currentTime);
		processTransform();
	}

	void ObjectRefInstance::processKey(real currentTime)
	{
		key->process(currentTime, resultObjectInterface);
	}

	void ObjectRefInstance::blendKey(real currentTime, real blendRatio)
	{
		key->blend(currentTime, blendRatio, resultObjectInterface);
	}

	void ObjectRefInstance::processTransform()
	{
		if (parentTransformer)
		{
			parentTransformer->setTrigFunctions();
			parentTransformer->transformChildObject(resultObjectInterface);
		}
		else
		{
			Settings::error("ObjectRefInstance::processTransform - parent transform processor missing");
		}
	}

	UniversalObjectInterface *ObjectRefInstance::resultObject() const
	{
		return resultObjectInterface;
	}

}
