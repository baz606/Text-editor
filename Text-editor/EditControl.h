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
	void SetTabLimit(int tabLimit);
	void SetMaxLimitText(UINT limit);
private:
	HWND hWnd;
	HWND parentWindowHandle;
	HFONT hDefFont;
};