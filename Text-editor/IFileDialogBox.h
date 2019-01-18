#pragma once

#include "NewWin.h"
#include <stringapiset.h>

const COMDLG_FILTERSPEC c_rgSaveTypes[] =
{
	{L"Text Document (*.txt)",       L_TEXT_FILE_EXTENSION},
	{L"All Files (*.*)"	 ,		     L"*.*"}
};

enum IFileDialogType
{
	OPEN, SAVE
};

class IFileDialogBox
{
public:
	IFileDialogBox();
	~IFileDialogBox();
	HRESULT CreateDialogBox(REFCLSID rCLSID, DWORD dwClsContext, REFIID refID, DWORD dFlags);
	LPSTR GetSelectedFilePath();

private:
	HRESULT SetOptions(DWORD dFlags);
	void SetDialogBoxType(REFCLSID rCLSID);

private:
	IFileDialog *iFileDialog;
	IFileDialogType dialogType;
};