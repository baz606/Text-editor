#include "Win32App.h"

Win32App::Win32App(int width, int height, LPCSTR title)
{
	CreateWindowApp(width, height, title);
}

LRESULT Win32App::CreateWindowApp(int width, int height, LPCSTR title)
{
	CreateWindowClassStruct(title);
	RegisterClassWindowApp();

	hWnd = CreateWindowEx(
		0, title, title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, GetModuleHandle(NULL), NULL
	);

	if (hWnd != nullptr)
	{
		ShowWindow(hWnd, SW_SHOW);
		return 0;
	}

	return -1;
}

LRESULT Win32App::CreateWindowClassStruct(LPCSTR className)
{
	wcEx = { 0 };

	wcEx.cbSize = sizeof(wcEx);
	wcEx.style = CS_OWNDC;
	wcEx.lpfnWndProc = WndProc;
	wcEx.cbClsExtra = 0;
	wcEx.cbWndExtra = 0;
	wcEx.hInstance = GetModuleHandle(nullptr);
	wcEx.hIcon = NULL;
	wcEx.hCursor = NULL;
	wcEx.hbrBackground = NULL;
	wcEx.lpszMenuName = NULL;
	wcEx.lpszClassName = className;
	wcEx.hIconSm = NULL;

	return 0;
}

ATOM Win32App::RegisterClassWindowApp()
{
	return RegisterClassEx(&wcEx);
}

HWND Win32App::GetHandle()
{
	return hWnd;
}

LRESULT CALLBACK Win32App::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
