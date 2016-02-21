#ifndef CF25POINTINSTANCEINFO_H
#define CF25POINTINSTANCEINFO_H

#include "Common.h"

#include "spriterengine/objectinfo/pointinstanceinfo.h"

namespace SpriterEngine
{

	class Cf25PointInstanceInfo : public PointInstanceInfo
	{
	public:
		Cf25PointInstanceInfo(LPRDATA rdPtr);

		void render() override;

	private:
		LPRDATA rdPtr;
	};

}

#endif // CF25POINTINSTANCEINFO_H
