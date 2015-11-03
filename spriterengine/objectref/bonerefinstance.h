#ifndef BONEREFINSTANCE_H
#define BONEREFINSTANCE_H

#include "objectrefinstance.h"

#include "transformprocessor.h"

namespace SpriterEngine
{

	class BoneRefInstance : public ObjectRefInstance
	{
	public:
		BoneRefInstance(UniversalObjectInterface *initialResultObject,
			TransformProcessor *initialParentTransformer,
			TransformProcessor *initialSelfTransformer,
			TimelineKey *initialKey);

		void process(real currentTime) override;

	private:
		TransformProcessor *transformProcessor;
	};

}

#endif // BONEREFINSTANCE_H
