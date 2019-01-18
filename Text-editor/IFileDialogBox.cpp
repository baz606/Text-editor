#include "IFileDialogBox.h"

IFileDialogBox::IFileDialogBox()
{
	iFileDialog = nullptr;
}

IFileDialogBox::~IFileDialogBox()
{
	iFileDialog->Release();
}

HRESULT IFileDialogBox::CreateDialogBox(REFCLSID rCLSID, DWORD dwClsContext, REFIID refID, DWORD dFlags)
{
	HRESULT hResult;
	hResult = CoCreateInstance(rCLSID, NULL, dwClsContext, refID, (void**)&iFileDialog);

	if (SUCCEEDED(hResult))
	{
		SetDialogBoxType(rCLSID);
		if (SUCCEEDED(SetOptions(dFlags)))
		{
			iFileDialog->SetDefaultExtension(L"");
			iFileDialog->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
			iFileDialog->Show(NULL);
		}
	}

	return hResult;
}

HRESULT IFileDialogBox::SetOptions(DWORD dFlags)
{
	DWORD dWord;
	HRESULT endResult;

	endResult = iFileDialog->GetOptions(&dWord);
	if (SUCCEEDED(endResult))
	{
		return iFileDialog->SetOptions(dWord | dFlags);
	}

	return endResult;
}

void IFileDialogBox::SetDialogBoxType(REFCLSID rCLSID)
{
	if (rCLSID == CLSID_FileOpenDialog)
	{
		dialogType = OPEN;
	}
	else if (rCLSID == CLSID_FileSaveDialog)
	{
		dialogType = SAVE;
	}
}