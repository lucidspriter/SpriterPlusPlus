
#include "Common.h"

bool Extension::IsAnimationPlayingByName(TCHAR* name)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		if (s == currentAnimationName)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Extension::HasCurrentAnimationFinished()
{
	if (IsScmlObjectValid())
	{
		if (scmlObj->isAnimationPlaying())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

long Extension::CompareCurrentTimeToValue(int val)
{
	return static_cast<int>(scmlObj->getCurrentTime());
}

bool Extension::IsScmlObjectValid()
{
	return (scmlModel.fileCount()>0 && scmlObj != NULL);
}

bool Extension::IsTagActive(TCHAR* tagName)
{
	wstring wsVar = wstring(tagName);
	string sVar(wsVar.begin(), wsVar.end());
	return scmlObj->tagIsActive(sVar);
}

bool Extension::IsObjectTagActive(TCHAR* objectName, TCHAR* tagName)
{
	wstring wsObj = wstring(objectName);
	string sObj(wsObj.begin(), wsObj.end());
	wstring wsTag = wstring(tagName);
	string sTag(wsTag.begin(), wsTag.end());
	return scmlObj->tagIsActive(sObj, sTag);
}

bool Extension::OnSoundEvent(TCHAR* soundName)
{
	wstring wstr = wstring(soundName);
	string name(wstr.begin(), wstr.end());
	return (SoundEvent.erase(name));
}

bool Extension::OnTriggerEvent(TCHAR* triggerName)
{
	wstring wstr = wstring(triggerName);
	string name(wstr.begin(), wstr.end());
	return (TriggerEvent.erase(name));
}


