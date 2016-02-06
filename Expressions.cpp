
#include "Common.h"

TCHAR * Extension::LastError()
{
	_tcscpy(errorTemp, lastError);
	_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[noError]);
	return  errorTemp;
}

TCHAR * Extension::CurrentAnimationName()
{
	TCHAR name[256];
	CA2T resStr(currentAnimationName.c_str());
	_tcscpy(name, resStr);
	return name;
}

int Extension::CurrentTime()
{
	return ((int)(scmlObj->getCurrentTime()));
}

float Extension::CurrentSpeedRatio()
{
	return speedRatio;
}

float Extension::GetScale()
{
	return rdPtr->rc->rcScaleX;
}

float Extension::GetAngle()
{
	return rdPtr->rc->rcAngle;
}

float Extension::GetRealVariable(TCHAR* variableName)
{
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	if (scmlObj->getVariable(sVar))
	{
		return scmlObj->getVariable(sVar)->getRealValue();
	}
	else
	{
		return 0.0;
	}
}

float Extension::GetObjectRealVariable(TCHAR* objectName, TCHAR* variableName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	if (scmlObj->getVariable(sObj, sVar))
	{
		return scmlObj->getVariable(sObj, sVar)->getRealValue();
	}
	else
	{
		return 0.0;
	}
}

int Extension::GetIntVariable(TCHAR* variableName)
{
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	if (scmlObj->getVariable(sVar))
	{
		return scmlObj->getVariable(sVar)->getIntValue();
	}
	else
	{
		return 0;
	}
}

int Extension::GetObjectIntVariable(TCHAR* objectName, TCHAR* variableName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	if (scmlObj->getVariable(sObj, sVar))
	{
		return scmlObj->getVariable(sObj, sVar)->getIntValue();
	}
	else
	{
		return 0;
	}
}

TCHAR* Extension::GetStringVariable(TCHAR* variableName)
{
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	if (scmlObj->getVariable(sVar))
	{
		CA2T res(scmlObj->getVariable(sVar)->getStringValue().c_str());
		return res;
	}
	else
	{
		return _T("");
	}
}

TCHAR* Extension::GetObjectStringVariable(TCHAR* objectName, TCHAR* variableName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	if (scmlObj->getVariable(sObj, sVar))
	{
		CA2T res(scmlObj->getVariable(sObj, sVar)->getStringValue().c_str());
		return res;
	}
	else
	{
		return _T("");
	}
}

int Extension::GetPointPosX(TCHAR* pointName)
{
	wstring wsVar = wstring(pointName);
	string sVar(wsVar.begin(), wsVar.end());
	SpriterEngine::UniversalObjectInterface *point = scmlObj->getObjectInstance(sVar);
	int res = 0;
	if (point != NULL)
	{
		res = (int)(point->getPosition().x + rhPtr->rhWindowX);
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[PointUnknown]);
	}
	return res;
}

int Extension::GetPointPosY(TCHAR* pointName)
{
	wstring wsVar = wstring(pointName);
	string sVar(wsVar.begin(), wsVar.end());
	SpriterEngine::UniversalObjectInterface *point = scmlObj->getObjectInstance(sVar);
	int res = 0;
	if (point != NULL)
	{
		res = (int)(point->getPosition().y + rhPtr->rhWindowY);
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[PointUnknown]);
	}
	return res;
}

float Extension::GetPointAngle(TCHAR* pointName)
{
	wstring wsVar = wstring(pointName);
	string sVar(wsVar.begin(), wsVar.end());
	SpriterEngine::UniversalObjectInterface *point = scmlObj->getObjectInstance(sVar);
	float res = 0.0;
	if (point != NULL)
	{
		if (flipX)
		{
			res = (float)(point->getAngle()+180);
		}
		else
		{
			res = (float)point->getAngle();
		}
		
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[PointUnknown]);
	}
	return res;
}