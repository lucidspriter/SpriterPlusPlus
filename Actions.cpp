
#include "Common.h"

void Extension::StopAnimation()
{
	animPlaying = false;
}
void Extension::StartAnimation()
{
	animPlaying = true;
}
void Extension::ChangeAnimationByName(TCHAR* name)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		scmlObj->setCurrentAnimation(s);
		currentAnimationName = s;
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::ChangeAnimationByNameWithBlending(TCHAR* name, int blendingTime)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		scmlObj->setCurrentAnimation(s,blendingTime);
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::ChangeAnimationTime(int timeMs)
{
	if (timeMs >= 0)
	{
		scmlObj->setCurrentTime(timeMs);
	}
}

void Extension::ChangeEntityByNumber(int num)
{
	if (IsScmlObjectValid())
	{
		scmlObj->setCurrentEntity(num);
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::SetFlipX(int enable)
{
	flipX = (enable>0);
}

void Extension::SetAnimationSpeed(float speed)
{
	if (speed >= 0)
	{
		speedRatio = speed;
	}
}

void Extension::ApplyCharacterMap(TCHAR* name)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		scmlObj->applyCharacterMap(s);
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::RemoveCharacterMap(TCHAR* name)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		scmlObj->removeCharacterMap(s);
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}
void Extension::RemoveAllCharacterMaps()
{
	if (IsScmlObjectValid())
	{
		scmlObj->removeAllCharacterMaps();
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::SetScale(float scale)
{
	if (IsScmlObjectValid())
	{
		rdPtr->rc->rcScaleX = rdPtr->rc->rcScaleY = scale;
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::SetAngle(float angle)
{
	if (IsScmlObjectValid())
	{
		rdPtr->rc->rcAngle =  angle;
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

void Extension::LoadSpriteFromActive(string spriteName, LPRO pObj, int nAnim, int nDir, int nFrame)
{
	if (pObj != NULL)
	{
		cSurface sprite;
		//to get animations
		LPOC ocPtr = pObj->roHo.hoCommon;
		LPAH ahPtr = (LPAH)((LPBYTE)ocPtr + ocPtr->ocAnimations);
		//if given n of animation bigger than number of animation, return with error
		if (nAnim > ahPtr->ahAnimMax)
		{
			return;
		}
		int nAnimOffset = ahPtr->ahOffsetToAnim[nAnim];
		if (nAnimOffset > 0) // if animation exists
		{
			LPAN anPtr = (LPAN)((LPBYTE)ahPtr + nAnimOffset);
			// anPtr contains a table of 32 offsets, one per direction.
			// At startup, the runtime fills in unknown values with the offsets 
			// of the closest directions (in editor only some of the directions are defined),
			// therefore all 32 offsets have valid values, greater than 0 (to be checked...). 
			int nDirOffset = anPtr->anOffsetToDir[nDir];
			if (nDirOffset > 0)
			{
				LPAD adPtr = (LPAD)((LPBYTE)anPtr + nDirOffset);
				if (nFrame < adPtr->adNumberOfFrame)
				{
					WORD imageNumber = (WORD)adPtr->adFrame[nFrame];
					SpriteSource[spriteName].imageNumber = imageNumber;
					SpriteSource[spriteName].pObj = pObj;
					SpriteSource[spriteName].loaded = false;
				}
			}
		}
	}
}

void Extension::LoadOrderedSprites(LPRO pObj, int nAnim)
{
	tinyxml2::XMLDocument doc;
	int nFolder = 0;
	int nFile = 0;
	if (doc.LoadFileFromBuffer(scmlFileString.c_str()) == tinyxml2::XML_SUCCESS)
	{
		tinyxml2::XMLElement* root = doc.FirstChildElement("spriter_data");
		if (root != NULL)
		{
			for (tinyxml2::XMLElement* folderChild = root->FirstChildElement("folder"); folderChild != NULL; folderChild = folderChild->NextSiblingElement("folder"))
			{
				for (tinyxml2::XMLElement* fileChild = folderChild->FirstChildElement("file"); fileChild != NULL; fileChild = fileChild->NextSiblingElement("file"))
				{
					LoadSpriteFromActive(fileChild->Attribute("name"), pObj, nAnim, nFolder, nFile);
					nFile++;
				}
				nFolder++;
				nFile = 0;
			}
		}
	}
}

void Extension::BoundBoxToObject(TCHAR* boxName, LPRO object)
{
	if (object != NULL)
	{
		wstring ws = wstring(boxName);
		string name(ws.begin(), ws.end());
		BoxLink[name] = object;
	}
}

void Extension::UnboundBoxFromObject(TCHAR* boxName)
{
	wstring ws = wstring(boxName);
	string name(ws.begin(), ws.end());
	BoxLink[name] = nullptr;
}

void Extension::SetDebug(int showBones, int showBoxes, int showPoints)
{
	SpriterEngine::Settings::renderDebugBones = (bool)showBones;
	SpriterEngine::Settings::renderDebugBoxes = (bool)showBoxes;
	SpriterEngine::Settings::renderDebugPoints = (bool)showPoints;
}