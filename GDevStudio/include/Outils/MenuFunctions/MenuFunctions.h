// MenuFunctions.h: Definitions of the MenuFunctins namespace functions
//
//	http://www.codeproject.com/KB/menus/MenusForBeginners.aspx
//
//////////////////////////////////////////////////////////////////////


#pragma once


namespace MenuFunctions  
{
	bool AddMenuItem(HMENU hTargetMenu, const CString& itemText, UINT itemID);
	bool AddMenuItem(HMENU hTargetMenu, const CString& itemText, UINT itemID, int* pInsertPositions);
	bool AddSeparator(HMENU hTargetMenu);
	
	UINT EnableMenuItem(HMENU hTargetMenu, UINT nIDEnableItem, BOOL bEnable);
	UINT CheckMenuItem(HMENU hTargetMenu, UINT nIDCheckItem, BOOL bCheck);


	int  CalculateMenuHeight(HMENU hMenu);
    int  CalculateMenuWidth(HMENU hMenu);
	bool EmptyMenu(HMENU hMenu);
};
