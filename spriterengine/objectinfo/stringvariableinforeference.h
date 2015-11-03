#ifndef STRINGVARIABLEINFOREFERENCE_H
#define STRINGVARIABLEINFOREFERENCE_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class StringVariableInfoReference : public UniversalObjectInterface
	{
	public:
		StringVariableInfoReference();

		std::string getStringValue() override;
		void setStringValue(std::string *newValue) override;

	private:
		std::string *value;
	};

}

#endif // STRINGVARIABLEINFOREFERENCE_H
