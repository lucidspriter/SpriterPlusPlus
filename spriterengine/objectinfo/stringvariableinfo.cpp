#include "stringvariableinfo.h"

namespace SpriterEngine
{

	StringVariableInfo::StringVariableInfo()
	{
	}

	std::string StringVariableInfo::getStringValue()
	{
		return value;
	}

	void StringVariableInfo::setStringValue(std::string newValue)
	{
		value = newValue;
	}

	void StringVariableInfo::setObjectTolinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setStringValue(&value);
	}

}
