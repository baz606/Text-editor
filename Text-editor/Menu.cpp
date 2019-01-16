#include "Menu.h"

Menu::Menu()
{
	hMenu = CreateMenu();
	Reset();
}

void Menu::AddSubMenuItem(LPCSTR subMenu, INT identifier)
{
	AppendMenu(hSubMenu, MF_STRING, identifier, subMenu);
}

void Menu::AddRootMenuItem(LPCSTR rootMenu)
{
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, rootMenu);
}

void Menu::SetMenuFor(HWND parentHandle)
{
	SetMenu(parentHandle, hMenu);
}

void Menu::Reset()
{
	hSubMenu = CreatePopupMenu();
}