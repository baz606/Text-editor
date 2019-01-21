#include "EditControl.h"

EditControl::EditControl(INT identified, INT width, INT height, DWORD dwStyle, HWND hParent)
{
	LoadLibrary(TEXT("Msftedit.dll"));

	hWnd = CreateWindowEx(
		NULL, "RICHEDIT50W", "", dwStyle,
		0, 0, width, height, hParent,(HMENU)identified,
		GetModuleHandle(NULL), NULL
	);

	parentWindowHandle = hParent;
	//SetWindowSubclass(hWnd, EditWndProc, IDC_MAIN_EDIT, NULL);
}

HWND EditControl::GetHandle()
{
	return hWnd;
}

void EditControl::ResizeWindow()
{
	RECT rcParent;
	GetClientRect(parentWindowHandle, &rcParent);

	SetWindowPos(hWnd, NULL, 0, 0, rcParent.right, rcParent.bottom, SWP_NOZORDER);
}

void EditControl::SetDefaultFont()
{
	hDefFont = CreateFont(18, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, NULL);

	SendMessage(hWnd, WM_SETFONT, (WPARAM)hDefFont, NULL);
}

void EditControl::SetFont(HFONT hFont)
{
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, NULL);
}

void EditControl::SetMargins(int top, int left, int right)
{
	SendMessage(hWnd, EM_SETMARGINS, MAKEWPARAM(EC_LEFTMARGIN, EC_RIGHTMARGIN), MAKELPARAM(left, right));

	RECT rcParent;
	GetClientRect(parentWindowHandle, &rcParent);
	SetWindowPos(hWnd, NULL, 0, top, rcParent.right, rcParent.bottom - top, SWP_NOZORDER);
}

void EditControl::SetTabLimit(int tabLimit)
{
	SendMessage(hWnd, EM_SETTABSTOPS, 1, (LPARAM)&tabLimit);
}

void EditControl::SetMaxLimitText(UINT limit)
{
	SendMessage(hWnd, EM_SETLIMITTEXT, (WPARAM)limit, 0);
}

BOOL EditControl::DisplayTextFromFile(LPSTR filePath)
{
	if (filePath != nullptr)
	{
		std::ifstream inputFileStream(filePath);
		std::stringstream ss;
		std::string temp, fileContents;

		if (inputFileStream.is_open())
		{
			while (getline(inputFileStream, temp))
			{
				ss << temp;
			}

			fileContents = ss.str();
			SetWindowText(hWnd, fileContents.c_str());
			inputFileStream.close();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	return FALSE;
}

BOOL EditControl::SaveTextToFile(LPSTR filePath)
{
	if (filePath != nullptr)
	{
		std::ofstream outputFileStream(filePath);
		if (outputFileStream.is_open())
		{
			LPSTR content;
			int length = GetWindowTextLength(hWnd);
			content = new CHAR[length + 1];
			GetWindowText(hWnd, content, length + 1);

			outputFileStream << content;
			outputFileStream.close();

			delete[] content;
			return TRUE;
		}
	}
	return FALSE;
}

LRESULT CALLBACK EditControl::EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, 
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{

	}
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}