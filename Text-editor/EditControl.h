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
	void SetDefaultCharFormat();
	void SetCharFormat(CHARFORMATA *charFormat);
	void SetMargins(int top, int left, int right);
	void SetTabLimit(int tabLimit);
	void SetMaxLimitText(UINT limit);
	void SetBackgroundColor(COLORREF newColor);
	BOOL DisplayTextFromFile(LPSTR filePath);
	BOOL SaveTextToFile(LPSTR filePath);
	COLORREF GetBackgroundColor();
private:
	HWND hWnd;
	HWND parentWindowHandle;
	HFONT hDefFont;
	CHARFORMATA charFormat;
	COLORREF backgroundColor;

private:
	static LRESULT CALLBACK EditWndProc(HWND hWnd, UINT uMsg, WPARAM wParam,
		LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
};