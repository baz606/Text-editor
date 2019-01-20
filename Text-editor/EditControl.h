#pragma once

#include "NewWin.h"
#include <fstream>
#include <sstream>
#include <string>

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
	BOOL DisplayTextFromFile(LPSTR filePath);
	BOOL SaveTextToFile(LPSTR filePath);
private:
	HWND hWnd;
	HWND parentWindowHandle;
	HFONT hDefFont;
	static LRESULT CALLBACK EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
};