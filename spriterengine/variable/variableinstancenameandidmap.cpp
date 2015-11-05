#include "variableinstancenameandidmap.h"

#include "../objectinfo/universalobjectinterface.h"

#include "variable.h"

namespace SpriterEngine
{

	VariableInstanceNameAndIdMap::VariableInstanceNameAndIdMap()
	{
	}

	VariableInstanceNameAndIdMap::~VariableInstanceNameAndIdMap()
	{
		for (auto& it : variables)
		{
			delete it;
		}
	}

	UniversalObjectInterface *VariableInstanceNameAndIdMap::getVariable(int variableIndex)
	{
		if(variableIndex<variables.size())
		{
			return variables.at(variableIndex);
		}
		else
		{
			// error
			return 0;
		}
	}

	UniversalObjectInterface *VariableInstanceNameAndIdMap::getVariable(std::string variableName)
	{
		auto it = variableNameMap.find(variableName);
		if (it != variableNameMap.end())
		{
			return (*it).second;
		}
		else
		{
			return 0;
			// error
		}
	}

	void VariableInstanceNameAndIdMap::pushBackVariable(Variable *variable)
	{
		variables.push_back(variable->getNewObjectInfoInstance(true));
		variableNameMap[variable->getName()] = variables.back();
	}

	bool VariableInstanceNameAndIdMap::isEmpty()
	{
		return variables.empty();
	}
}
