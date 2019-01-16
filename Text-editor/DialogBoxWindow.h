#pragma once

#include "NewWin.h"

class DialogBoxWindow
{
public:
	INT CreateDialogBox(HINSTANCE handle,LPCSTR title, INT identifier, HWND parentHandle);
	static LPCSTR dialogBoxtitle;

private:
	static BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};