#pragma once

#include "NewWin.h"

class Win32App
{
public:
	Win32App(int width, int height, LPCSTR title);
	HWND GetHandle();
private:
	LRESULT CreateWindowApp(int width, int height, LPCSTR title);
	LRESULT CreateWindowClassStruct(LPCSTR className);
	ATOM RegisterClassWindowApp();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	HWND hWnd;
	WNDCLASSEX wcEx;
};
