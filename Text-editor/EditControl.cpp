#include "EditControl.h"
#include "IFileDialogBox.h"

EditControl::EditControl(INT identified, INT width, INT height, DWORD dwStyle, HWND hParent)
{
	LoadLibrary(TEXT("Msftedit.dll"));

	backgroundColor = RGB(83, 87, 94);
	parentWindowHandle = hParent;

	hWnd = CreateWindowEx(
		NULL, "RICHEDIT50W", "", dwStyle,
		0, 0, width, height, hParent,(HMENU)identified,
		GetModuleHandle(NULL), NULL
	);

	SetDefaultCharFormat();
	SetTabLimit(TAB_LIMIT);
	SetMaxLimitText(MAX_LIMIT);
	SetBackgroundColor(backgroundColor);

	SetWindowSubclass(hWnd, EditWndProcInterm, IDC_MAIN_EDIT, DWORD_PTR(this));
	RegisterHotKey(hWnd, IDC_MAIN_EDIT, MOD_CONTROL, 'S');
	RegisterHotKey(hWnd, IDC_MAIN_EDIT, MOD_CONTROL, 'O');
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

void EditControl::SetDefaultCharFormat()
{
	charFormat = { 0 };
	charFormat.cbSize = sizeof(charFormat);
	charFormat.crTextColor = RGB(255, 255, 255);
	charFormat.dwMask = CFM_COLOR | CFM_BOLD;
	charFormat.dwEffects = CFE_BOLD;

	SendMessage(hWnd, EM_SETCHARFORMAT, (WPARAM)SCF_ALL, (LPARAM)(&charFormat));
}

void EditControl::SetCharFormat(CHARFORMATA *charFormat)
{
	SendMessage(hWnd, EM_SETCHARFORMAT, (WPARAM)SCF_ALL, (LPARAM)(&charFormat));
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

COLORREF EditControl::GetBackgroundColor()
{
	return backgroundColor;
}

void EditControl::SetBackgroundColor(COLORREF newColor)
{
	backgroundColor = newColor;
	SendMessage(hWnd, EM_SETBKGNDCOLOR, 0, (LPARAM)backgroundColor);
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
				ss << temp << std::endl;
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

LRESULT CALLBACK EditControl::EditWndProcInterm(HWND hWnd, UINT uMsg, WPARAM wParam, 
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	EditControl *edc = (EditControl*)dwRefData;
	return edc->EditWndProc(hWnd, uMsg, wParam, lParam, uIdSubclass, dwRefData);
}

LRESULT CALLBACK EditControl::EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
	LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{
		case WM_HOTKEY:
		{
			int low_word = LOWORD(lParam);
			int high_word = HIWORD(lParam);

			if (low_word == MOD_CONTROL && high_word == 'O')
			{
				SendMessage(parentWindowHandle, WM_COMMAND, MAKEWPARAM(ID_FILE_OPEN, 0), 0);
			}
			else if (low_word == MOD_CONTROL && high_word == 'S')
			{
				SendMessage(parentWindowHandle, WM_COMMAND, MAKEWPARAM(ID_FILE_SAVEAS, 0), 0);
			}
		}
		break;
	}

	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}