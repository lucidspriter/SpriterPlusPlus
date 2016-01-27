#pragma once

// #define TGFEXT       // TGF2, MMF2, MMF2 Dev
   #define MMFEXT       // MMF2, MMF2 Dev
// #define PROEXT       // MMF2 Dev only

#define _USE_MATH_DEFINES

#include <sstream>
#include <unordered_map>
#include  "Edif.h"
#include "Resource.h"
#include "atlstr.h"

enum ErrorN
{
	noError,
	PointUnknown,
	AnimationUnknown,
	ActiveUnknown,
	ObjectUnknown,
	ScmlObjectInvalid,
};

static TCHAR* ErrorS[6] = {
	_T("[00] No Error"),
	_T("[01] Point does not exist or is invalid."),
	_T("[02] Animation does not exist or is invalid."),
	_T("[03] Active object does not exist or is invalid."),
	_T("[04] Spriter object does not exist or is invalid"),
	_T("[05] ScmlObject is invalid."),
};

#include	<map>

// tinyxml2
#include "tinyxml2\tinyxml2.h"

// overridden factories to create our special cf25 and TinyXml based objects
#include "override/cf25objectfactory.h"
#include "override/cf25filefactory.h"

// include to use Spriter animations
#include "spriterengine/spriterengine.h"
#include "spriterengine/global/settings.h"

#ifndef PATH_MAX
    #define PATH_MAX MAX_PATH
#endif

#ifndef MAX_ELTS
#define MAX_ELTS 256
#endif


// edPtr : Used at edittime and saved in the MFA/CCN/EXE files

struct EDITDATA
{
	// Header - required
	extHeader		eHeader;

	// Object's data
	wchar_t			scmlFilename[_MAX_PATH];
	char			scmlFile[1];//scml file buffer, dynamic size

};

typedef struct 
{
	LPRO pObj;
	WORD imageNumber;
	bool loaded;
}Sprite;

#include "Extension.h"
