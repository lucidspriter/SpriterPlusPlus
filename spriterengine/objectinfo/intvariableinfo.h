#ifndef INTVARIABLEINFO_H
#define INTVARIABLEINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class IntVariableInfo : public UniversalObjectInterface
	{
	public:
		IntVariableInfo();

		int getIntValue() override;
		void setIntValue(int newValue) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		int value;
	};

}

#endif // INTVARIABLEINFO_H
