#include "DialogBoxWindow.h"

LPCSTR DialogBoxWindow::dialogBoxtitle = ""; //Initializing static member variable

INT DialogBoxWindow::CreateDialogBox(HINSTANCE handleInstance, LPCSTR title, INT identifier, HWND parentHandle)
{
	dialogBoxtitle = title;
	return DialogBox(handleInstance, MAKEINTRESOURCE(identifier), parentHandle, AboutDlgProc);
}

BOOL CALLBACK DialogBoxWindow::AboutDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		//Setting the About Dialog box position to the centre of the screen
		RECT wRect;
		GetClientRect(hWnd, &wRect);
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		std::string output = "LEFT: " + std::to_string(wRect.left) + ", TOP: " + std::to_string(wRect.top) +
			", RIGHT: " + std::to_string(wRect.right) + ", BOTTOM: " + std::to_string(wRect.bottom);

		SetWindowText(hWnd, dialogBoxtitle);
		SetWindowPos(hWnd, NULL, (screenWidth - wRect.right) / 2, (screenHeight - wRect.bottom) / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

		return TRUE;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			EndDialog(hWnd, IDOK);
		}
		break;
		case IDCANCEL:
		{
			EndDialog(hWnd, IDCANCEL);
		}
		break;
		default:
			return FALSE;
		}
	}
	break;
	default:
		return FALSE;
	}

	return TRUE;
}