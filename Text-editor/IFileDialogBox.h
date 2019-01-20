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

private:
	// Inner class
	class CDialogEventHandler : public IFileDialogEvents
	{
	private:
		IFileDialogBox *parentFileDialogBox;
	public:
		CDialogEventHandler(IFileDialogBox *fileDialogBox)
		{
			parentFileDialogBox = fileDialogBox;
		}
		virtual HRESULT STDMETHODCALLTYPE OnFileOk(IFileDialog *pfd) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnFolderChanging(IFileDialog *pfd, IShellItem *psiFolder) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnFolderChange(IFileDialog *pfd) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnSelectionChange(IFileDialog *pfd) override
		{
			HRESULT hr = S_OK;
			//OutputDebugString("OnSelectionChange called!!\n");
			switch (parentFileDialogBox->dialogType)
			{
				case SAVE:
				{
					UINT fileTypeIndex;
					hr = pfd->GetFileTypeIndex(&fileTypeIndex);

					//Checking whether its a text file
					//It would be better to convert it to a switch if we are adding more file extensions
					if (wcscmp(c_rgSaveTypes[fileTypeIndex - 1].pszSpec, L_TEXT_FILE_EXTENSION) == 0)
					{
						hr = pfd->SetDefaultExtension(L"txt");
					}
					else
					{
						hr = pfd->SetDefaultExtension(L"");
					}
				}
			}

			return hr;
		}

		virtual HRESULT STDMETHODCALLTYPE OnShareViolation(IFileDialog *pfd, IShellItem *psi, FDE_SHAREVIOLATION_RESPONSE *pResponse) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnTypeChange(IFileDialog *pfd) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE OnOverwrite(IFileDialog *pfd, IShellItem *psi, FDE_OVERWRITE_RESPONSE *pResponse) override
		{
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override
		{
			return S_OK;
		}

		virtual ULONG STDMETHODCALLTYPE AddRef(void) override
		{
			return 3;
		}

		virtual ULONG STDMETHODCALLTYPE Release(void) override
		{
			return 2;
		}
	};
	CDialogEventHandler *eventHandler;
};