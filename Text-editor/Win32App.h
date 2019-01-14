#pragma once

#include "EditControl.h"

class Win32App
{
public:
	Win32App(int width, int height, LPCSTR title);
	~Win32App();
	HWND GetHandle();
private:
	LRESULT CreateWindowApp(int width, int height, LPCSTR title);
	LRESULT CreateWindowClassStruct(LPCSTR className);
	ATOM RegisterClassWindowApp();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WndProcInitial(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcInterm(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HWND hWnd;
	WNDCLASSEX wcEx;
	EditControl *editControl;
};
