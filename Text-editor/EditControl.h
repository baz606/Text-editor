#pragma once

#include "NewWin.h"

class EditControl
{
public:
	EditControl(INT identified, INT width, INT height, DWORD dwStyle, HWND hParent);
	HWND GetHandle();
	void ResizeWindow(HWND hParent);
private:
	HWND hWnd;
};