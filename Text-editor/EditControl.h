#pragma once

#include "NewWin.h"

class EditControl
{
public:
	EditControl(INT identified, INT width, INT height, DWORD dwStyle, HWND hParent);
	HWND GetHandle();
	void ResizeWindow();
	void SetDefaultFont();
	void SetFont(HFONT hFont);
	void SetMargins(int top, int left, int right);
private:
	HWND hWnd;
	HWND parentWindowHandle;
	HFONT hDefFont;
};