#pragma once

#include "NewWin.h"
#include <vector>

class Menu
{
public:
	Menu();
	~Menu();
	void AddMenuItemsFor(LPCSTR rootItem, LPCSTR *subMenuItems);
	void AddMenuItemsFor(LPCSTR rootItem, std::vector<LPCSTR> &subMenuItems);

private:
	HMENU hMenu;
	HMENU hSubMenu;
};
