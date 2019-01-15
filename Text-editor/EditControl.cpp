#include "EditControl.h"

EditControl::EditControl(INT identified, INT width, INT height, DWORD dwStyle, HWND hParent)
{
	hWnd = CreateWindowEx(
		NULL, "Edit", "", dwStyle,
		0, 0, width, height, hParent,(HMENU)identified,
		GetModuleHandle(NULL), NULL
	);

	parentWindowHandle = hParent;
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