
#include "Common.h"

/*!
* \file Actions.cpp
* \brief Actions available in Spriter object
* \author conceptgame
* \version 0.8
*/


/*!
*  \brief Stop animation
*
*  Freeze the time of the current animation
*/
void Extension::StopAnimation()
{
	animPlaying = false;
}

/*!
*  \brief Start animation
*
*  Elapsed time affects the renderer
*/
void Extension::StartAnimation()
{
	animPlaying = true;
}

/*!
*  \brief ChangeAnimationByName
*
*  Change the current animation to the specified animation
*  lecture
*
*  \param name : animation name to set
*/
void Extension::ChangeAnimationByName(TCHAR* name)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		if (scmlObj->getEntity(0)->animationExists(s))
		{
			scmlObj->setCurrentAnimation(s);
			scmlObj->startResumePlayback();
			currentAnimationName = s;
		}
		else
		{
			_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[AnimationUnknown]);
		}
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

/*!
*  \brief ChangeAnimationByNameWithBlending
*
*  Change the current animation to the specified animation
*  lecture
*
*  \param name : animation name to set
*/
void Extension::ChangeAnimationByNameWithBlending(TCHAR* name, int blendingTime)
{
	if (IsScmlObjectValid())
	{
		wstring ws = wstring(name);
		string s(ws.begin(), ws.end());
		if (scmlObj->getEntity(0)->animationExists(s))
		{
			scmlObj->setCurrentAnimation(s, blendingTime);
			scmlObj->startResumePlayback();
			currentAnimationName = s;
		}
		else
		{
			_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[AnimationUnknown]);
		}
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ScmlObjectInvalid]);
	}
}

/*!
*  \brief ChangeAnimationTime
*
*  Change the time in current animation
*
*  \param timeMs : time in ms to set
*/
void Extension::ChangeAnimationTime(int timeMs)
{
	if (timeMs >= 0)
	{
		scmlObj->setCurrentTime(timeMs);
	}
}

/*!
*  \brief ChangeEntityByNumber
*
*  Change the entity
*
*  \param num : entity number to set
*/
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

/*!
*  \brief SetFlipX
*
*  Flip the whole rendering of the object on the X axis
*
*  \param enable : <=0 means disabled, >0 means enabled
*/
void Extension::SetFlipX(int enable)
{
	flipX = (enable>0);
}

/*!
*  \brief SetAnimationSpeed
*
*  Set the speed ratio of the current animation 
*
*  \param speed : <0 is an invalid value (no change), >=0 set the speed ratio (2 => twice faster, 0.5 => twice slower) 
*/
void Extension::SetAnimationSpeed(float speed)
{
	if (speed >= 0)
	{
		speedRatio = speed;
	}
}

/*!
*  \brief ApplyCharacterMap
*
*  Apply the specified character map
*
*  \param name : name of the character map to apply (see RemoveCharacterMap to undo)
*/
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

/*!
*  \brief RemoveCharacterMap
*
*  Remove the specified character map
*
*  \param name : name of the character map to remove (see ApplyCharacterMap to apply a new one)
*/
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

/*!
*  \brief RemoveAllCharacterMaps
*
*  Remove all applied character maps
*
*/
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

/*!
*  \brief SetScale
*
*  Set scale on both X and Y axis
*
*  \param scale : scale value to apply
*/
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

/*!
*  \brief SetAngle
*
*  Rotate the whole object of the specified angle in degree
*
*  \param scale : angle in degree
*/
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

/*!
*  \brief LoadSpriteFromActive
*
*  Load one sprite from an active object by a specific animation on a specific direction from a specific frame number
*
*  \param spriteName : sprite name in the spriter file
*  \param pObj : active object to use as library
*  \param nAnim : animation number to choose from
*  \param nDir : direction to choose from
*  \param nFrame : frame number of the sprite to clone in spriter object
*/
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
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ActiveUnknown]);
	}
}

/*!
*  \brief LoadOrderedSpritesPerAnimation
*
*  Load all sprites from an active object in the specified animation given that the sprites are ordered 
*  by direction for folder and per frame for sprites
*
*  \param pObj : active object to use as library
*  \param nAnim : animation number to choose from
*/
void Extension::LoadOrderedSpritesPerAnimation(LPRO pObj, int nAnim)
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

/*!
*  \brief LoadOrderedSpritesPerDirection
*
*  Load all sprites from an active object in the specified animation 
*  given that the sprites are ordered one after each other in one direction only
*
*  \param pObj : active object to use as library
*  \param nAnim : animation number to choose from
*  \param nDir : direction to choose from
*/
void Extension::LoadOrderedSpritesPerDirection(LPRO pObj, int nAnim, int nDir)
{
	tinyxml2::XMLDocument doc;
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
					LoadSpriteFromActive(fileChild->Attribute("name"), pObj, nAnim, nDir, nFile);
					nFile++;
				}
			}
		}
	}
}

/*!
*  \brief BoundBoxToObject
*
*  Bound position(x and y), scale and angle from an active object to a box object in spriter
*
*  \param boxName : box name in spriter file
*  \param pObj : active object to use as box
*/
void Extension::BoundBoxToObject(TCHAR* boxName, LPRO object)
{
	if (object != NULL)
	{
		wstring ws = wstring(boxName);
		string name(ws.begin(), ws.end());
		BoxLink[name] = object;
	}
	else
	{
		_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[ObjectUnknown]);
	}
}

/*!
*  \brief UnboundBoxFromObject
*
*  Unbound position(x and y), scale and angle of a box object from the corresponding active object
*
*  \param boxName : box name in spriter file
*/
void Extension::UnboundBoxFromObject(TCHAR* boxName)
{
	wstring ws = wstring(boxName);
	string name(ws.begin(), ws.end());
	BoxLink[name] = nullptr;
}

/*!
*  \brief SetDebug
*
*  Unbound position(x and y), scale and angle of a box object from the corresponding active object
*
*  \param showBones : !=0 means show bones on screen
*  \param showBoxes : !=0 means show boxes on screen
*  \param showPoints : !=0 means show points on screen
*/
void Extension::SetDebug(int showBones, int showBoxes, int showPoints)
{
	SpriterEngine::Settings::renderDebugBones = (bool)showBones;
	SpriterEngine::Settings::renderDebugBoxes = (bool)showBoxes;
	SpriterEngine::Settings::renderDebugPoints = (bool)showPoints;
}