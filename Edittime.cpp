
// ============================================================================
//
// This file contains routines that are handled only during the Edittime,
// under the Frame and Event editors.
//
// Including creating, display, and setting up your object.
// 
// ============================================================================

#include "Common.h"

#if !defined(RUN_ONLY)

// PROPERTIES /////////////////////////////////////////////////////////////////

// Property identifiers
enum {
	PROPID_SETTINGS = PROPID_EXTITEM_CUSTOM_FIRST,
	PROPID_FILEPARAMETER_TITLE,
	PROPID_SPRITER_FILE_PATH,
// Example
// -------
//	PROPID_TEXTTITLE,	
//	PROPID_TEXT,	
//	PROPID_CHECK,
//	PROPID_COMBO,
//	PROPID_COLOR,

};

FilenameCreateParam fcpScml = { MAKEINTRESOURCE(IDS_SPRITERFILEFILTER), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY };

// Example of content of the PROPID_COMBO combo box
//LPCSTR ComboList[] = {
//	0,	// reserved
//	MAKEINTRESOURCE(IDS_FIRSTOPTION),	
//	MAKEINTRESOURCE(IDS_SECONDOPTION),	
//	MAKEINTRESOURCE(IDS_THIRDOPTION),	
//	NULL
//};

// Property definitions
//
// Type, ID, Text, Text of Info box [, Options, Init Param]
//
PropData Properties[] = {

// Example
// -------
//	PropData_Group		(PROPID_TEXTTITLE,	IDS_PROP_TEXTTITLE,		IDS_PROP_TEXTTITLE),
//	PropData_EditString	(PROPID_TEXT,		IDS_PROP_TEXT,			IDS_PROP_TEXT_INFO),
//	PropData_CheckBox	(PROPID_CHECK,		IDS_PROP_CHECK,			IDS_PROP_CHECK_INFO),
//	PropData_ComboBox	(PROPID_COMBO,		IDS_PROP_COMBO,			IDS_PROP_COMBO,	ComboList),
//	PropData_Color		(PROPID_COLOR,		IDS_PROP_COLOR,			IDS_PROP_COLOR_INFO),
	PropData_Group		(PROPID_FILEPARAMETER_TITLE, (int)_T("Spriter File"), (int)_T("Spriter File")),
	PropData_Filename	(PROPID_SPRITER_FILE_PATH,(int)_T("File path"),(int)_T("Set the path for the spriter file"),&fcpScml),

	// End of table (required)
	PropData_End()
};


#endif // !defined(RUN_ONLY)


// ============================================================================
//
// ROUTINES USED UNDER FRAME EDITOR
// 
// ============================================================================


// --------------------
// MakeIcon
// --------------------
// Called once object is created or modified, just after setup.
// Also called before showing the "Insert an object" dialog if your object
// has no icon resource

int WINAPI DLLExport MakeIconEx ( mv _far *mV, cSurface* pIconSf, LPTSTR lpName, fpObjInfo oiPtr, LPEDATA edPtr )
{
#ifndef RUN_ONLY

    pIconSf->Delete();
    pIconSf->Clone(*SDK->Icon);

    pIconSf->SetTransparentColor(RGB(255, 0, 255));

#endif // !defined(RUN_ONLY)
   return 0;
}

static wstring GetDirectory(wchar_t* scmlFilename)
{
	wstring directory = L"";
	wstring path = wstring(scmlFilename);
	const size_t last_slash_idx = path.rfind('\\');
	if (std::wstring::npos != last_slash_idx)
	{
		directory = path.substr(0, last_slash_idx);
	}
	directory = directory + L"\\";
	return directory;
}

static bool CopySprites(wchar_t* scmlFilename, string scmlFile)
{
	wstringstream outStr;
	int id = 0;
	wstring inDirectory = GetDirectory(scmlFilename);
	wstring outDirectory = inDirectory + L"CF25Import";
	wstring folderDirectory = outDirectory + L"\\folder";
	tinyxml2::XMLDocument doc;
	int nFolder = 0;
	int nFile = 0;
	
	if (doc.LoadFileFromBuffer(scmlFile.c_str()) == tinyxml2::XML_SUCCESS)
	{
		//create out directory
		if (!CreateDirectory(outDirectory.c_str(), NULL))
		{
			if (GetLastError() != ERROR_ALREADY_EXISTS)
			{
				return false;
			}
		}
		tinyxml2::XMLElement* root = doc.FirstChildElement("spriter_data");
		if (root != NULL)
		{
			for (tinyxml2::XMLElement* folderChild = root->FirstChildElement("folder"); folderChild != NULL; folderChild = folderChild->NextSiblingElement("folder"))
			{
				outStr << folderDirectory << nFolder;
				if (!CreateDirectory(outStr.str().c_str(), NULL))
				{
					if (GetLastError() != ERROR_ALREADY_EXISTS)
					{
						return false;
					}
				}
				outStr.str(std::wstring());
				outStr.clear();
				for (tinyxml2::XMLElement* fileChild = folderChild->FirstChildElement("file"); fileChild != NULL; fileChild = fileChild->NextSiblingElement("file"))
				{
					wstring fileIn;
					string sName = fileChild->Attribute("name");
					fileIn.assign(sName.begin(), sName.end());
					fileIn = inDirectory + fileIn;
					outStr << folderDirectory << nFolder << "\\sprite." << nFile << L".png";
					wstring fileOut = outStr.str();

					if (!CopyFileW(fileIn.c_str(), fileOut.c_str(), false))
					{
						DWORD error = GetLastError();
						return false;
					}
					outStr.str(std::wstring());
					outStr.clear();
					nFile++;
				}
				nFolder++;
				nFile = 0;
			}
		}
	}
	return true;
}

// --------------------
// CreateFromFile
// --------------------
// Creates a new object from file
//
void WINAPI	DLLExport CreateFromFile(LPMV mV, LPTSTR fileName, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	// Initialize your extension data from the given file
	
	if (fileName)
	{
		//Load the whole scml object
		char* scmlFile = nullptr;
		_tcscpy(edPtr->scmlFilename, fileName);
		tinyxml2::XMLDocument doc;
		doc.LoadFileToBuffer(fileName, &scmlFile);
		doc.Clear();
		int copy = MessageBox(0, _T("Do you want to copy all sprites to import in CF2.5?"), _T("Warning"), MB_YESNO | MB_ICONWARNING);
		if (copy == IDYES)
		{
			if (!CopySprites(fileName, scmlFile))
			{
					MessageBox(0, _T("Error by copying sprites."), _T("Error"), MB_OK | MB_ICONERROR);
			}
		}
				
		//Update EDIDATA Structure
		DWORD dwNewSize = sizeof(EDITDATA) + strlen(scmlFile)+1;
		// Asks MMF to reallocate the structure with the new size
		LPEDATA pNewPtr = (LPEDATA)mvReAllocEditData(mV, edPtr, dwNewSize);
			
		// If reallocation worked
		if (pNewPtr!=NULL)
		{
			// Copy the string
			edPtr=pNewPtr;
			strcpy(edPtr->scmlFile, scmlFile);
		}
		
		//delete temporary buffer
		delete[] scmlFile;
		scmlFile = nullptr;
	}
	else
	{
		_tcscpy(edPtr->scmlFilename, _T(""));
	}

#endif // !defined(RUN_ONLY)
}

// --------------------
// CreateObject
// --------------------
// Called when you choose "Create new object". It should display the setup box 
// and initialize everything in the datazone.

int WINAPI DLLExport CreateObject(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY

	// Check compatibility
	if ( IS_COMPATIBLE(mV) )
	{
        Edif::Init(mV, edPtr);

		// Set default object settings
//		edPtr->swidth = 48;
//		edPtr->sheight = 48;
		CreateFromFile(mV, NULL, edPtr);

        return 0;
	}
#endif // !defined(RUN_ONLY)

	// Error
	return -1;
}

// --------------------
// SetEditSize
// --------------------
// Called when the object has been resized
//
// Note: remove the comments if your object can be resized (and remove the comments in the .def file)

BOOL WINAPI SetEditSize(LPMV mv, LPEDATA edPtr, int cx, int cy)
{
#ifndef RUN_ONLY
	/*edPtr->swidth = cx;
	edPtr->sheight = cy;*/
#endif // !defined(RUN_ONLY)
	return TRUE;	// OK
}


// --------------------
// PutObject
// --------------------
// Called when each individual object is dropped in the frame.
//
void WINAPI	DLLExport PutObject(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr, ushort cpt)
{
#ifndef RUN_ONLY
	
#endif // !defined(RUN_ONLY)
}

// --------------------
// RemoveObject
// --------------------
// Called when each individual object is removed from the frame.
//
void WINAPI	DLLExport RemoveObject(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr, ushort cpt)
{
#ifndef RUN_ONLY
	// Is the last object removed?
    if (0 == cpt)
	{
        Edif::Free(edPtr);

		// Do whatever necessary to remove our data
	}
#endif // !defined(RUN_ONLY)
}

// --------------------
// DuplicateObject
// --------------------
// Called when an object is created from another one (note: should be called CloneObject instead...)
//
void WINAPI DLLExport DuplicateObject(mv __far *mV, fpObjInfo oiPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetObjectRect
// --------------------
// Returns the size of the rectangle of the object in the frame editor.
//
void WINAPI DLLExport GetObjectRect(mv _far *mV, RECT FAR *rc, fpLevObj loPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	rc->right = rc->left + SDK->Icon->GetWidth();	
	rc->bottom = rc->top + SDK->Icon->GetHeight();
#endif // !defined(RUN_ONLY)
	return;
}


// --------------------
// EditorDisplay
// --------------------
// Displays the object under the frame editor
//

void WINAPI DLLExport EditorDisplay(mv _far *mV, fpObjInfo oiPtr, fpLevObj loPtr, LPEDATA edPtr, RECT FAR *rc)
{
#ifndef RUN_ONLY

	LPSURFACE winSurf = WinGetSurface((int) mV->mvIdEditWin);

	if(!winSurf)
        return;
	SDK->Icon->Blit(*winSurf, rc->left, rc->top, BMODE_TRANSP, BOP_COPY, 0);
#endif // !defined(RUN_ONLY)
}


// --------------------
// IsTransparent
// --------------------
// This routine tells MMF2 if the mouse pointer is over a transparent zone of the object.
// 

extern "C" BOOL WINAPI DLLExport IsTransparent(mv _far *mV, fpLevObj loPtr, LPEDATA edPtr, int dx, int dy)
{
#ifndef RUN_ONLY
	// Write your code here
#endif // !defined(RUN_ONLY)
	return FALSE;
}

// --------------------
// PrepareToWriteObject
// --------------------
// Just before writing the datazone when saving the application, MMF2 calls this routine.
// 
void WINAPI	DLLExport PrepareToWriteObject(mv _far *mV, LPEDATA edPtr, fpObjInfo adoi)
{
#ifndef RUN_ONLY

	// Write your code here
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetFilters
// --------------------

BOOL WINAPI GetFilters(LPMV mV, LPEDATA edPtr, DWORD dwFlags, LPVOID pReserved)
{
#ifndef RUN_ONLY
	// If your extension uses image filters
	if ( (dwFlags & GETFILTERS_IMAGES) != 0 )
		return TRUE;

	// If your extension uses sound filters
//	if ( (dwFlags & GETFILTERS_SOUNDS) != 0 )
//		return TRUE;
#endif // RUN_ONLY
	return FALSE;
}

// --------------------
// UsesFile
// --------------------
// Triggers when a file is dropped onto the frame
// Return TRUE if you can create an object from the given file
//
BOOL WINAPI	DLLExport UsesFile (LPMV mV, LPTSTR fileName)
{
	BOOL r = FALSE;
#ifndef RUN_ONLY

	// Example: return TRUE if file extension is ".scml"
	
	LPTSTR	ext, npath;

	if (fileName != NULL)
	{
		if ((ext = (LPTSTR)calloc(_MAX_EXT, sizeof(TCHAR))) != NULL)
		{
			if ((npath = (LPTSTR)calloc(_MAX_PATH, sizeof(TCHAR))) != NULL)
			{
				_tcscpy(npath, fileName);
				_tsplitpath(npath, NULL, NULL, NULL, ext);
				if (_tcsicmp(ext, _T(".scml")) == 0)
					r = TRUE;
				free(npath);
			}
			free(ext);
		}
	}
#endif // !defined(RUN_ONLY)
	return r;
}

// ============================================================================
//
// PROPERTIES
// 
// ============================================================================

// --------------------
// GetProperties
// --------------------
// Inserts properties into the properties of the object.
//
BOOL WINAPI DLLExport GetProperties(LPMV mV, LPEDATA edPtr, BOOL bMasterItem)
{
#ifndef RUN_ONLY
	mvInsertProps(mV, edPtr, Properties, PROPID_TAB_GENERAL, TRUE);
#endif // !defined(RUN_ONLY)

	// OK
	return TRUE;
}

// --------------------
// ReleaseProperties
// --------------------
// Called when the properties are removed from the property window.
//
void WINAPI DLLExport ReleaseProperties(LPMV mV, LPEDATA edPtr, BOOL bMasterItem)
{
#ifndef RUN_ONLY
	// Write your code here
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetPropCreateParam
// --------------------
// Called when a property is initialized and its creation parameter is NULL (in the PropData).
// Allows you, for example, to change the content of a combobox property according to specific settings in the EDITDATA structure.
//
LPARAM WINAPI DLLExport GetPropCreateParam(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	// Example
	// -------
//	if ( nPropID == PROPID_COMBO )
//	{
//		switch (edPtr->sType)
//		{
//		case TYPE1:
//			return (LPARAM)ComboList1;
//		case TYPE2:
//			return (LPARAM)ComboList2;
//		}
//	}
#endif // !defined(RUN_ONLY)
	return NULL;
}

// ----------------------
// ReleasePropCreateParam
// ----------------------
// Called after a property has been initialized.
// Allows you, for example, to free memory allocated in GetPropCreateParam.
//
void WINAPI DLLExport ReleasePropCreateParam(LPMV mV, LPEDATA edPtr, UINT nPropID, LPARAM lParam)
{
#ifndef RUN_ONLY
#endif // !defined(RUN_ONLY)
}

// --------------------
// GetPropValue
// --------------------
// Returns the value of properties that have a value.
// Note: see GetPropCheck for checkbox properties
//
LPVOID WINAPI DLLExport GetPropValue(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	// Example
	// -------
	switch (nPropID) 
	{
//
//	// Returns a color.
//	case PROPID_COLOR:
//		return new CPropDWordValue(edPtr->dwColor);
//
//	// Returns a string
//	case PROPID_TEXT:
//		return new CPropDataValue(&edPtr->szText[0]);
//
//	// Returns the value of the combo box
//	case PROPID_COMBO:
//		return new CPropDWordValue(edPtr->nComboIndex);
		case PROPID_SPRITER_FILE_PATH:
		{
			return new CPropStringValue(edPtr->scmlFilename);
			break;
		}
	}

#endif // !defined(RUN_ONLY)
	return NULL;
}

// --------------------
// GetPropCheck
// --------------------
// Returns the checked state of properties that have a check box.
//
BOOL WINAPI DLLExport GetPropCheck(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	// Example
	// -------
//	switch (nPropID) {
//
//	// Return 0 (unchecked) or 1 (checked)
//	case PROPID_CHECK:
//		return edPtr->nCheck;
//	}

#endif // !defined(RUN_ONLY)
	return 0;		// Unchecked
}

// --------------------
// SetPropValue
// --------------------
// This routine is called by MMF after a property has been modified.
//
void WINAPI DLLExport SetPropValue(LPMV mV, LPEDATA edPtr, UINT nPropID, LPVOID lParam)
{
#ifndef RUN_ONLY
	// Gets the pointer to the CPropValue structure
	CPropValue* pValue = (CPropValue*)lParam;

	// Example
	// -------
	switch (nPropID) {
		//
		//	case PROPID_COMBO:
		//		// Simply grab the value
		//		edPtr->nComboIndex = ((CPropDWordValue*)pValue)->m_dwValue;
		//		break;

		//	case PROPID_COLOR:
		//		// Here too, gets the value
		//		edPtr->dwColor = ((CPropDWordValue*)pValue)->m_dwValue;
		//		break;

		//	case PROPID_TEXT:
		//		{
		//			// Gets the string
		//			LPSTR pStr = (LPSTR)((CPropDataValue*)pValue)->m_pData;
		//
		//			// You can simply poke the string if your EDITDATA structure has a fixed size,
		//			// or have an adaptive size of structure like below
		//
		//			// If the length is different
		//			if (strlen(pStr)!=strlen(edPtr->text))
		//			{
		//				// Asks MMF to reallocate the structure with the new size
		//				LPEDATA pNewPtr = (LPEDATA)mvReAllocEditData(mV, edPtr, sizeof(EDITDATA)+strlen(pStr));
		//				
		//				// If reallocation worked
		//				if (pNewPtr!=NULL)
		//				{
		//					// Copy the string
		//					edPtr=pNewPtr;
		//					strcpy(edPtr->text, pStr);
		//				}
		//			}
		//			else
		//			{	
		//				// Same size : simply copy
		//				strcpy(edPtr->text, pStr);
		//			}
		//		}
		//		break;

		case PROPID_SPRITER_FILE_PATH:
		{
			// Gets the string
			LPTSTR pStr = (LPTSTR)((CPropStringValue*)pValue)->GetString();

			// You can simply poke the string if your EDITDATA structure has a fixed size,
			// or have an adaptive size of structure like below
			CreateFromFile(mV, pStr, edPtr);
			break;
		}
	}
		
	// You may want to have your object redrawn in the frame editor after the modifications,
	// in this case, just call this function
	// mvInvalidateObject(mV, edPtr);

#endif // !defined(RUN_ONLY)
}

// --------------------
// SetPropCheck
// --------------------
// This routine is called by MMF when the user modifies a checkbox in the properties.
//
void WINAPI DLLExport SetPropCheck(LPMV mV, LPEDATA edPtr, UINT nPropID, BOOL nCheck)
{
#ifndef RUN_ONLY
	// Example
	// -------
//	switch (nPropID)
//	{
//	case PROPID_CHECK:
//		edPtr->nCheck = nCheck;
//		mvInvalidateObject(mV, edPtr);
//		mvRefreshProp(mV, edPtr, PROPID_COMBO, TRUE);
//		break;
//	}
#endif // !defined(RUN_ONLY)
}

// --------------------
// EditProp
// --------------------
// This routine is called when the user clicks the button of a Button or EditButton property.
//
BOOL WINAPI DLLExport EditProp(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY

	if (nPropID == PROPID_SPRITER_FILE_PATH)
	{
		CreateFromFile(mV, edPtr->scmlFilename, edPtr);
	}

#endif // !defined(RUN_ONLY)
	return FALSE;
}

// --------------------
// EditObject
// --------------------
// Called when the user selects the Edit command in the object's popup menu
//
BOOL WINAPI EditObject(mv _far *mV, fpObjInfo oiPtr, fpLevObj loPtr, LPEDATA edPtr)
{
#ifndef RUN_ONLY
	// Check compatibility
	if (IS_COMPATIBLE(mV))
	{
		//return EditProp(mV, edPtr, PROPID_SPRITER_FILE_PATH);
	}
#endif // !defined(RUN_ONLY)
	return FALSE;
}

// --------------------
// IsPropEnabled
// --------------------
// This routine returns the enabled state of a property.
//
BOOL WINAPI IsPropEnabled(LPMV mV, LPEDATA edPtr, UINT nPropID)
{
#ifndef RUN_ONLY
	// Example
	// -------
/*
	switch (nPropID) {

	case PROPID_CHECK:
		return (edPtr->nComboIndex != 0);
	}
*/
#endif // !defined(RUN_ONLY)
	return TRUE;
}


// ============================================================================
//
// TEXT PROPERTIES
// 
// ============================================================================

// --------------------
// GetTextCaps
// --------------------
// Return the text capabilities of the object under the frame editor.
//
DWORD WINAPI DLLExport GetTextCaps(mv _far *mV, LPEDATA edPtr)
{
	return 0;	// (TEXT_ALIGN_LEFT|TEXT_ALIGN_HCENTER|TEXT_ALIGN_RIGHT|TEXT_ALIGN_TOP|TEXT_ALIGN_VCENTER|TEXT_ALIGN_BOTTOM|TEXT_FONT|TEXT_COLOR);
}

// --------------------
// GetTextFont
// --------------------
// Return the font used the object.
// Note: the pStyle and cbSize parameters are obsolete and passed for compatibility reasons only.
//
BOOL WINAPI DLLExport GetTextFont(mv _far *mV, LPEDATA edPtr, LPLOGFONT plf, LPTSTR pStyle, UINT cbSize)
{
#if !defined(RUN_ONLY)
	// Example: copy LOGFONT structure from EDITDATA
	// memcpy(plf, &edPtr->m_lf, sizeof(LOGFONT));
#endif // !defined(RUN_ONLY)

	return TRUE;
}

// --------------------
// SetTextFont
// --------------------
// Change the font used the object.
// Note: the pStyle parameter is obsolete and passed for compatibility reasons only.
//
BOOL WINAPI DLLExport SetTextFont(mv _far *mV, LPEDATA edPtr, LPLOGFONT plf, LPCSTR pStyle)
{
#if !defined(RUN_ONLY)
	// Example: copy LOGFONT structure to EDITDATA
	// memcpy(&edPtr->m_lf, plf, sizeof(LOGFONT));
#endif // !defined(RUN_ONLY)

	return TRUE;
}

// --------------------
// GetTextClr
// --------------------
// Get the text color of the object.
//
COLORREF WINAPI DLLExport GetTextClr(mv _far *mV, LPEDATA edPtr)
{
	// Example
	return 0;	// edPtr->fontColor;
}

// --------------------
// SetTextClr
// --------------------
// Set the text color of the object.
//
void WINAPI DLLExport SetTextClr(mv _far *mV, LPEDATA edPtr, COLORREF color)
{
	// Example
	//edPtr->fontColor = color;
}

// --------------------
// GetTextAlignment
// --------------------
// Get the text alignment of the object.
//
DWORD WINAPI DLLExport GetTextAlignment(mv _far *mV, LPEDATA edPtr)
{
	DWORD dw = 0;
#if !defined(RUN_ONLY)
	// Example
	// -------
/*	if ( (edPtr->eData.dwFlags & ALIGN_LEFT) != 0 )
		dw |= TEXT_ALIGN_LEFT;
	if ( (edPtr->eData.dwFlags & ALIGN_HCENTER) != 0 )
		dw |= TEXT_ALIGN_HCENTER;
	if ( (edPtr->eData.dwFlags & ALIGN_RIGHT) != 0 )
		dw |= TEXT_ALIGN_RIGHT;
	if ( (edPtr->eData.dwFlags & ALIGN_TOP) != 0 )
		dw |= TEXT_ALIGN_TOP;
	if ( (edPtr->eData.dwFlags & ALIGN_VCENTER) != 0 )
		dw |= TEXT_ALIGN_VCENTER;
	if ( (edPtr->eData.dwFlags & ALIGN_BOTTOM) != 0 )
		dw |= TEXT_ALIGN_BOTTOM;
*/
#endif // !defined(RUN_ONLY)
	return dw;
}

// --------------------
// SetTextAlignment
// --------------------
// Set the text alignment of the object.
//
void WINAPI DLLExport SetTextAlignment(mv _far *mV, LPEDATA edPtr, DWORD dwAlignFlags)
{
#if !defined(RUN_ONLY)
	// Example
	// -------
/*	DWORD dw = edPtr->eData.dwFlags;

	if ( (dwAlignFlags & TEXT_ALIGN_LEFT) != 0 )
		dw = (dw & ~(ALIGN_LEFT|ALIGN_HCENTER|ALIGN_RIGHT)) | ALIGN_LEFT;
	if ( (dwAlignFlags & TEXT_ALIGN_HCENTER) != 0 )
		dw = (dw & ~(ALIGN_LEFT|ALIGN_HCENTER|ALIGN_RIGHT)) | ALIGN_HCENTER;
	if ( (dwAlignFlags & TEXT_ALIGN_RIGHT) != 0 )
		dw = (dw & ~(ALIGN_LEFT|ALIGN_HCENTER|ALIGN_RIGHT)) | ALIGN_RIGHT;

	if ( (dwAlignFlags & TEXT_ALIGN_TOP) != 0 )
		dw = (dw & ~(ALIGN_TOP|ALIGN_VCENTER|ALIGN_BOTTOM)) | ALIGN_TOP;
	if ( (dwAlignFlags & TEXT_ALIGN_VCENTER) != 0 )
		dw = (dw & ~(ALIGN_TOP|ALIGN_VCENTER|ALIGN_BOTTOM)) | ALIGN_VCENTER;
	if ( (dwAlignFlags & TEXT_ALIGN_BOTTOM) != 0 )
		dw = (dw & ~(ALIGN_TOP|ALIGN_VCENTER|ALIGN_BOTTOM)) | ALIGN_BOTTOM;

	edPtr->eData.dwFlags = dw;
*/
#endif // !defined(RUN_ONLY)
}


// ----------------------------------------------------------
// Custom Parameters
// ----------------------------------------------------------

// --------------------
// InitParameter
// --------------------
// Initialize the parameter.
//
void WINAPI InitParameter(mv _far *mV, short code, paramExt* pExt)
{
#if !defined(RUN_ONLY)
	// Example
	// -------
	// strcpy(&pExt->pextData[0], "Parameter Test");
	// pExt->pextSize = sizeof(paramExt) + strlen(pExt->pextData)+1;
#endif // !defined(RUN_ONLY)
}

// Example of custom parameter setup proc
// --------------------------------------
/*
#if !defined(RUN_ONLY)
BOOL CALLBACK DLLExport SetupProc(HWND hDlg, UINT msgType, WPARAM wParam, LPARAM lParam)
{
	paramExt*			pExt;

	switch (msgType)
	{
		case WM_INITDIALOG: // Init dialog

			// Save edptr
			SetWindowLong(hDlg, DWL_USER, lParam);
			pExt=(paramExt*)lParam;

			SetDlgItemText(hDlg, IDC_EDIT, pExt->pextData);
			return TRUE;

		case WM_COMMAND: // Command

			// Retrieve edptr
			pExt = (paramExt *)GetWindowLong(hDlg, DWL_USER);

			switch (wmCommandID)
			{
			case IDOK:	// Exit
				GetDlgItemText(hDlg, IDC_EDIT, pExt->pextData, 500);
				pExt->pextSize=sizeof(paramExt)+strlen(pExt->pextData)+1;
				EndDialog(hDlg, TRUE);
				return TRUE;

				default:
					break;
			}
			break;

		default:
			break;
	}
	return FALSE;
}
#endif // !defined(RUN_ONLY)
*/

// --------------------
// EditParameter
// --------------------
// Edit the parameter.
//
void WINAPI EditParameter(mv _far *mV, short code, paramExt* pExt)
{
#if !defined(RUN_ONLY)

	// Example
	// -------
	// DialogBoxParam(hInstLib, MAKEINTRESOURCE(DB_TRYPARAM), mV->mvHEditWin, SetupProc, (LPARAM)(LPBYTE)pExt);

#endif // !defined(RUN_ONLY)
}

// --------------------
// GetParameterString
// --------------------
// Initialize the parameter.
//
void WINAPI GetParameterString(mv _far *mV, short code, paramExt* pExt, LPSTR pDest, short size)
{
#if !defined(RUN_ONLY)

	// Example
	// -------
	// wsprintf(pDest, "Super parameter %s", pExt->pextData);

#endif // !defined(RUN_ONLY)
}
