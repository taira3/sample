#include "StdAfx.h"
#include "UXCore.h"

#include <commctrl.h>

UXCore::UXCore(void)
{
}

UXCore::~UXCore(void)
{
}


// UIïîïiÇÃçÏê¨
HWND UXCore::UiFactory(int kind)
{
	HWND	hWnd = NULL;

	switch (kind)
	{
	case 0:
		break;
	}
	return hWnd;
}

//
int UXCore::AddPage()
{
	//
	TCITEM tc_item;
	tc_item.mask = TCIF_TEXT;
	tc_item.pszText = _T("Page");
	TabCtrl_InsertItem(hBase, 0, &tc_item);

	//

	return 0;
}

//
HWND UXCore::CreateBase(HWND client_hwnd, HINSTANCE hInstance)
{
	HWND hwnd = NULL;
	
	RECT	rc;
	if (GetClientRect(client_hwnd, &rc))
	{
		InitCommonControls();
		hwnd = CreateWindowEx(
			0, 
			WC_TABCONTROL, 
			NULL,
			WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
			0, 0, 
			rc.right, rc.bottom, 
			client_hwnd, 
			(HMENU)NULL,
			hInstance, 
			NULL
		);
	}
	return hwnd ;
}
