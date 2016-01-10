#ifndef CF25BONEINSTANCEINFO_H
#define CF25BONEINSTANCEINFO_H

#include "Common.h"

#include "spriterengine/objectinfo/boneinstanceinfo.h"

namespace SpriterEngine
{

	class Cf25BoneInstanceInfo : public BoneInstanceInfo
	{
	public:
		Cf25BoneInstanceInfo(point initialSize, LPRDATA rdPtr);

		void render() override;

	private:
		LPRDATA rdPtr;
		POINT pts[4];
	};

}

#endif // CF25BONEINSTANCEINFO_H
