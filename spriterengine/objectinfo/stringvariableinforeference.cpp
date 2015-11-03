#include "stringvariableinforeference.h"

namespace SpriterEngine
{

	StringVariableInfoReference::StringVariableInfoReference() :
		value(0)
	{
	}

	std::string StringVariableInfoReference::getStringValue()
	{
		if (value)
		{
			return *value;
		}
		else
		{
			return "";
		}
	}

	void StringVariableInfoReference::setStringValue(std::string *newValue)
	{
		value = newValue;
	}

}
