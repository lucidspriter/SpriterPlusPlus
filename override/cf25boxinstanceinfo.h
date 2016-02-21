#ifndef CF25BOXINSTANCEINFO_H
#define CF25BOXINSTANCEINFO_H

#include "Common.h"

#include "spriterengine/objectinfo/boxinstanceinfo.h"

namespace SpriterEngine
{

	class Cf25BoxInstanceInfo : public BoxInstanceInfo
	{
	public:
		Cf25BoxInstanceInfo(point initialSize, LPRDATA rdPtr, Extension* ext);

		void render() override;

	private:
		LPRDATA rdPtr;
		Extension *ext;
		POINT pts[4];
	};

}

#endif // CF25BOXINSTANCEINFO_H
