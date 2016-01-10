
#include "Common.h"


///
/// EXTENSION CONSTRUCTOR/DESTRUCTOR
///

Extension::Extension(LPRDATA _rdPtr, LPEDATA edPtr, fpcob cobPtr)
	: rdPtr(_rdPtr), rhPtr(_rdPtr->rHo.hoAdRunHeader), Runtime(_rdPtr), scmlFileString(edPtr->scmlFile),
	scmlModel("dummy.scml", new SpriterEngine::Cf25FileFactory(rdPtr,this), new SpriterEngine::Cf25ObjectFactory(rdPtr,this))
{
	#ifdef _DEBUG
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		printf("Create one object Spriter:\n");
	#endif

    /*
        Link all your action/condition/expression functions to their IDs to match the
        IDs in the JSON here
    */

	LinkAction(0, StopAnimation);
	LinkAction(1, StartAnimation);
	LinkAction(2, ChangeAnimationByName);
	LinkAction(3, ChangeAnimationTime);
	LinkAction(4, SetFlipX);
	LinkAction(5, SetAnimationSpeed);
	LinkAction(6, ApplyCharacterMap);
	LinkAction(7, SetScale);
	LinkAction(8, SetAngle);
	LinkAction(9, LoadSpriteFromActive);
	LinkAction(10, LoadOrderedSprites);
	LinkAction(11, ChangeEntityByNumber);
	LinkAction(12, ChangeAnimationByNameWithBlending);
	LinkAction(13, RemoveCharacterMap);
	LinkAction(14, RemoveAllCharacterMaps);
	LinkAction(15, BoundBoxToObject);
	LinkAction(16, UnboundBoxFromObject);
	LinkAction(17, SetDebug);
    
	LinkCondition(0, IsAnimationPlayingByName);
	LinkCondition(1, HasCurrentAnimationFinished);
	LinkCondition(2, CompareCurrentTimeToValue);
	LinkCondition(3, IsTagActive);
	LinkCondition(4, IsObjectTagActive);
	LinkCondition(5, OnSoundEvent);
	LinkCondition(6, OnTriggerEvent);

	LinkExpression(0, LastError);
	LinkExpression(1, GetScale);
	LinkExpression(2, GetAngle);
	LinkExpression(3, CurrentTime);
	LinkExpression(4, CurrentSpeedRatio);
	LinkExpression(5, CurrentAnimationName);
	LinkExpression(6, GetRealVariable);
	LinkExpression(7, GetObjectRealVariable);
	LinkExpression(8, GetIntVariable);
	LinkExpression(9, GetObjectIntVariable);
	LinkExpression(10, GetStringVariable);
	LinkExpression(11, GetObjectStringVariable);
	LinkExpression(12, GetPointPosX);
	LinkExpression(13, GetPointPosY);
	LinkExpression(14, GetPointDirection);
	
    /*
        This is where you'd do anything you'd do in CreateRunObject in the original SDK

        It's the only place you'll get access to edPtr at runtime, so you should transfer
        anything from edPtr to the extension class here.
    
    */
	_snwprintf_s(lastError, _countof(lastError), ERRORSIZE, ErrorS[noError]);
	_snwprintf_s(errorTemp, _countof(errorTemp), ERRORSIZE, ErrorS[noError]);
	deltaTime = 0;
	currentSystemTime = GetTickCount();
	animPlaying = false;
	flipX = false;
	speedRatio = 1.0f;
	displayRect = { 0, 0, 0, 0 };
		
	scmlObj = scmlModel.getNewEntityInstance(0);//assume first entity at start
}

Extension::~Extension()
{
    /*
        This is where you'd do anything you'd do in DestroyRunObject in the original SDK.
        (except calling destructors and other such atrocities, because that's automatic in Edif)
    */
}


short Extension::Handle()
{
    /*
       If your extension will draw to the MMF window you should first 
       check if anything about its display has changed :

           if (rdPtr->roc.rcChanged)
              return REFLAG_DISPLAY;
           else
              return 0;

       You will also need to make sure you change this flag yourself 
       to 1 whenever you want to redraw your object
     
       If your extension won't draw to the window, but it still needs 
       to do something every MMF loop use :

            return 0;

       If you don't need to do something every loop, use :

            return REFLAG_ONESHOT;

       This doesn't mean this function can never run again. If you want MMF
       to handle your object again (causing this code to run) use this function:

            Runtime.Rehandle();

       At the end of the loop this code will run

    */
	if (IsScmlObjectValid())
	{
		return REFLAG_DISPLAY;
	}
	else
	{
		return 0;
	}
}


short Extension::Display()
{
	/*
	   If you return REFLAG_DISPLAY in Handle() this routine will run.
	   */

	// Ok
	if (IsScmlObjectValid())
	{
		LPSURFACE psw = WinGetSurface((int)rhPtr->rhIdEditWin);
		deltaTime = GetTickCount() - currentSystemTime;
		currentSystemTime = GetTickCount();
		int posX = rdPtr->rHo.hoX - rhPtr->rhWindowX;
		int posY = rdPtr->rHo.hoY - rhPtr->rhWindowY;
		if (!animPlaying)
		{
			deltaTime = 0;
		}
		scmlObj->setPosition(SpriterEngine::point((double)(posX), (double)(posY)));
		scmlObj->setAngle(SpriterEngine::toRadians(rdPtr->rc->rcAngle));
		scmlObj->setScale(SpriterEngine::point(flipX ? -rdPtr->rc->rcScaleX : rdPtr->rc->rcScaleX, rdPtr->rc->rcScaleY));
		scmlObj->setTimeElapsed(deltaTime*speedRatio);
		displayRect = { posX - 1, posY - 1, posX + 1, posY + 1 };//reset display rectangle before rendering
		scmlObj->render();
		scmlObj->playAllTriggers();
		//update CF25 display properties
		rdPtr->rHo.hoRect = displayRect;
		/*#ifdef DEBUG
		psw->Rectangle(rdPtr->rHo.hoRect.left, rdPtr->rHo.hoRect.top, rdPtr->rHo.hoRect.right, rdPtr->rHo.hoRect.bottom, 3, BLUE);
		#endif*/
		rdPtr->rHo.hoImgWidth = rdPtr->rHo.hoRect.right - rdPtr->rHo.hoRect.left;
		rdPtr->rHo.hoImgHeight = rdPtr->rHo.hoRect.bottom - rdPtr->rHo.hoRect.top;
		rdPtr->rHo.hoImgXSpot = posX - rdPtr->rHo.hoRect.left;
		rdPtr->rHo.hoImgYSpot = posY - rdPtr->rHo.hoRect.top;
		WinAddZone(rhPtr->rhIdEditWin, &rdPtr->rHo.hoRect);

		SpriterEngine::UniversalObjectInterface *colBox = nullptr;
		//update collision box objects
		for (auto it = BoxLink.begin(); it != BoxLink.end(); ++it)
		{
			if (it->second != nullptr)
			{
				colBox = scmlObj->getObjectInstance(it->first);
				if (colBox != nullptr)
				{
					if (it->second->roHo.hoImgWidth != colBox->getSize().x || it->second->roHo.hoImgHeight != colBox->getSize().y)
					{
						//it->second->roc.rcScaleX = (colBox->getSize().x / it->second->roHo.hoImgWidth);
						//it->second->roc.rcScaleY = (colBox->getSize().y / it->second->roHo.hoImgHeight);
						it->second->roHo.hoImgXSpot = colBox->getSize().x*colBox->getPivot().x;
						it->second->roHo.hoImgYSpot = colBox->getSize().y*colBox->getPivot().y;
						//it->second->roHo.hoRect
					}
					float w = colBox->getSize().x;
					float h = colBox->getSize().y;
					float pivx = colBox->getPivot().x;
					float pivy = colBox->getPivot().y;
					float scalex = colBox->getScale().x;
					float scaley = colBox->getScale().y;
					LPRO testObj = it->second;
					it->second->roc.rcAngle = SpriterEngine::toDegrees(colBox->getAngle());
					it->second->roc.rcScaleX = scalex;
					it->second->roc.rcScaleY = scaley;
					it->second->roHo.hoX = /*-(it->second->roHo.hoImgXSpot - w*pivx)*(w / it->second->roHo.hoImgWidth)*/ + colBox->getPosition().x + rhPtr->rhWindowX;
					it->second->roHo.hoY = /*-(it->second->roHo.hoImgYSpot - h*pivy)*(h / it->second->roHo.hoImgHeight)*/ + colBox->getPosition().y + rhPtr->rhWindowY;
					//it->second->roHo.hoImgXSpot = w*pivx;
					//it->second->roHo.hoImgYSpot = h*pivy;
					it->second->roc.rcChanged = true;
				}
			}
		}
			
	}
	return 0;
}

short Extension::Pause()
{

    // Ok
    return 0;
}

short Extension::Continue()
{

    // Ok
    return 0;
}

bool Extension::Save(HANDLE File)
{
	bool OK = false;

    #ifndef VITALIZE

	    // Save the object's data here

	    OK = true;

    #endif

	return OK;
}

bool Extension::Load(HANDLE File)
{
	bool OK = false;

    #ifndef VITALIZE

	    // Load the object's data here

	    OK = true;

    #endif

	return OK;
}

// These are called if there's no function linked to an ID

void Extension::Action(int ID, LPRDATA rdPtr, long param1, long param2)
{

}

long Extension::Condition(int ID, LPRDATA rdPtr, long param1, long param2)
{

    return false;
}

long Extension::Expression(int ID, LPRDATA rdPtr, long param)
{

    return 0;
}

