#ifndef REALVARIABLEINFO_H
#define REALVARIABLEINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class RealVariableInfo : public UniversalObjectInterface
	{
	public:
		RealVariableInfo();

		real getRealValue() override;
		void setRealValue(real newValue) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		real value;
	};

}

#endif // REALVARIABLEINFO_H
