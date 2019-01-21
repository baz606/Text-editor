#include "IFileDialogBox.h"

IFileDialogBox::IFileDialogBox()
{
	iFileDialog = nullptr;
	eventHandler = new CDialogEventHandler(this);
}

IFileDialogBox::~IFileDialogBox()
{
	if (iFileDialog != nullptr)
	{
		iFileDialog->Release();
	}
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
			DWORD dWord;
			iFileDialog->SetDefaultExtension(L"");
			iFileDialog->Advise(eventHandler, &dWord);
			iFileDialog->SetFileTypes(ARRAYSIZE(c_rgSaveTypes), c_rgSaveTypes);
			iFileDialog->Show(NULL);
		}
	}

	return hResult;
}

LPSTR IFileDialogBox::GetSelectedFilePath()
{
	HRESULT hResult;
	if (iFileDialog != nullptr)
	{
		IShellItem *selectedFile;
		hResult = iFileDialog->GetResult(&selectedFile);
		if (SUCCEEDED(hResult))
		{
			LPWSTR filePath = nullptr;
			selectedFile->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

			//Convert LPWSTR to LPSTR
			LPSTR convertedFilePath = new char[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, filePath, MAX_PATH, convertedFilePath, MAX_PATH, NULL, NULL);

			selectedFile->Release();

			return convertedFilePath;
		}
	}

	return NULL;
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