#include "Win32App.h"

Win32App::Win32App(int width, int height, LPCSTR title, HINSTANCE hInstance)
{
	className = title;
	this->hInstance = hInstance;
	CreateWindowApp(width, height, title);
}

Win32App::~Win32App()
{
	UnregisterClass(className, hInstance);
	
	delete editControl;
	delete dialogBox;
}

LRESULT Win32App::CreateWindowApp(int width, int height, LPCSTR title)
{
	CreateWindowClassStruct(title);
	RegisterClassWindowApp();

	hWnd = CreateWindowEx(
		0, title, title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL, NULL, GetModuleHandle(NULL), this
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
	wcEx.lpfnWndProc = WndProcInitial;
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

HINSTANCE Win32App::GetHInstance()
{
	return hInstance;
}

LRESULT CALLBACK Win32App::WndProcInitial(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW *pCreate = (CREATESTRUCTW*)lParam;
		Win32App *pWin = (Win32App*)(pCreate->lpCreateParams);
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)pWin);
		
		SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProcInterm);

		return pWin->WndProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Win32App::WndProcInterm(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Win32App *pWin = (Win32App*)GetWindowLong(hWnd, GWL_USERDATA);

	return pWin->WndProc(hWnd, uMsg, wParam, lParam);
}

void Win32App::AddMenuSystem(HWND hWnd)
{
	Menu menu;

	menu.AddSubMenuItem("Open", ID_FILE_OPEN);
	menu.AddSubMenuItem("SaveAs", ID_FILE_SAVEAS);
	menu.AddSubMenuItem("Exit", ID_FILE_EXIT);
	menu.AddRootMenuItem("File");
	menu.SetMenuFor(hWnd);
	menu.Reset();

	menu.AddSubMenuItem("About", ID_HELP_ABOUT);
	menu.AddRootMenuItem("Help");
	menu.SetMenuFor(hWnd);
	menu.Reset();
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
		case WM_CREATE:
		{
			editControl = new EditControl(IDC_MAIN_EDIT, 640, 480,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN,
				hWnd);

			AddMenuSystem(hWnd);
		}
		break;
		case WM_SIZE:
		{
			editControl->ResizeWindow();
			editControl->SetDefaultFont();
			editControl->SetMargins(TOP_MARGIN, LEFT_MARGIN, 0);
			editControl->SetTabLimit(TAB_LIMIT);
			editControl->SetMaxLimitText(MAX_LIMIT);
		}
		break;
		case WM_COMMAND:
		{
			int low_word = LOWORD(wParam);
			int high_word = HIWORD(wParam);
			switch (low_word)
			{
				case ID_HELP_ABOUT:
				{
					dialogBox = new DialogBoxWindow();
					dialogBox->CreateDialogBox(hInstance, "About", IDD_DIALOG1, hWnd);
				}
			}
		}
		break;
		case WM_ERASEBKGND:
		{
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

			RECT rect;
			GetClientRect(hWnd, &rect);

			FillRect((HDC)wParam, &rect, hBrush);
		}
		break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
