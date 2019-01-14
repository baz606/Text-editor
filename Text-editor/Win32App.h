#pragma once

#include "EditControl.h"

class Win32App
{
public:
	Win32App(int width, int height, LPCSTR title, HINSTANCE hInstance);
	~Win32App();
	HWND GetHandle();
	HINSTANCE GetHInstance();
private:
	LRESULT CreateWindowApp(int width, int height, LPCSTR title);
	LRESULT CreateWindowClassStruct(LPCSTR className);
	ATOM RegisterClassWindowApp();
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK WndProcInitial(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcInterm(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	HWND hWnd;
	HINSTANCE hInstance;
	WNDCLASSEX wcEx;
	EditControl *editControl;
	LPCSTR className;
};
