#ifndef CF25IMAGEFILE_H
#define CF25IMAGEFILE_H

#include "spriterengine/override/imagefile.h"

#include "Common.h"

namespace SpriterEngine
{
	class Cf25ImageFile : public ImageFile
	{
	public:
		Cf25ImageFile(std::string initialFilePath, point initialDefaultPivot, LPRDATA rdPtr, Extension *ext);

		void renderSprite(UniversalObjectInterface *spriteInfo) override;

	private:
		cSurface sprite;
		LPRDATA rdPtr;
		Extension *ext;

		void RotateRectangle(RECT &r, const POINT center, const float angle);
		void RotatePoint(POINT &p, const POINT c, const float a);
	};

}

#endif // CF25IMAGEFILE_H
