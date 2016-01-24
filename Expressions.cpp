
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
	return scmlObj->getVariable(sVar)->getRealValue();
}

float Extension::GetObjectRealVariable(TCHAR* objectName, TCHAR* variableName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	return scmlObj->getVariable(sObj,sVar)->getRealValue();
}

int Extension::GetIntVariable(TCHAR* variableName)
{
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	return scmlObj->getVariable(sVar)->getIntValue();
}

int Extension::GetObjectIntVariable(TCHAR* objectName, TCHAR* variableName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	return scmlObj->getVariable(sObj, sVar)->getIntValue();
}

TCHAR* Extension::GetStringVariable(TCHAR* variableName)
{
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	CA2T res(scmlObj->getVariable(sVar)->getStringValue().c_str());
	return res;
}

TCHAR* Extension::GetObjectStringVariable(TCHAR* objectName, TCHAR* variableName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsVar = wstring(variableName);
	string sVar(wsVar.begin(), wsVar.end());
	CA2T res(scmlObj->getVariable(sObj, sVar)->getStringValue().c_str());
	return res;
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
	return res;
}

float Extension::GetPointDirection(TCHAR* pointName)
{
	wstring wsVar = wstring(pointName);
	string sVar(wsVar.begin(), wsVar.end());
	SpriterEngine::UniversalObjectInterface *point = scmlObj->getObjectInstance(sVar);
	float res = 0.0;
	if (point != NULL)
	{
		res = (float)point->getAngle();
	}
	return res;
}