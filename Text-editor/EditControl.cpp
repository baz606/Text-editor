#include "EditControl.h"

EditControl::EditControl(INT identified, INT width, INT height, DWORD dwStyle, HWND hParent)
{
	hWnd = CreateWindowEx(
		NULL, "Edit", "", dwStyle,
		0, 0, width, height, hParent,(HMENU)identified,
		GetModuleHandle(NULL), NULL
	);
}

HWND EditControl::GetHandle()
{
	return hWnd;
}

void EditControl::ResizeWindow(HWND hParent)
{
	RECT rcParent;
	GetClientRect(hParent, &rcParent);

	SetWindowPos(hWnd, NULL, CW_USEDEFAULT, CW_USEDEFAULT, rcParent.right, rcParent.bottom, SWP_NOZORDER);
}