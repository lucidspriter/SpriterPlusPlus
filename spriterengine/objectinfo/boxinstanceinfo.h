#ifndef BOXINSTANCEINFO_H
#define BOXINSTANCEINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class BoxInstanceInfo : public UniversalObjectInterface
	{
	public:
		BoxInstanceInfo(point initialSize);

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		point getPivot() override;
		point getSize() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setPivot(const point &newPivot) override;

		void setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

		void render() override;

	private:
		point position;
		AngleInfo angle;
		point scale;
		point pivot;

		point size;
	};

}

#endif // BOXINSTANCEINFO_H
