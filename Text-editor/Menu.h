#pragma once

#include "NewWin.h"

class Menu
{
public:
	Menu();
	void AddSubMenuItem(LPCSTR subMenu, INT identifier);
	void AddRootMenuItem(LPCSTR rootMenu);
	void SetMenuFor(HWND parentHandle);
	void Reset();

private:
	HMENU hMenu;
	HMENU hSubMenu;
};
