#pragma once

#include <vector>

class UXCore
{
public:
	UXCore(void);
	UXCore(HWND v1, HINSTANCE v2) :
		hwnd(v1),
		hInstance(v2)
	{
		hBase = CreateBase(hwnd, hInstance);
	};
	~UXCore(void);
	// UIïîïiÇÃçÏê¨
	HWND UiFactory(int kind);

private:
	HWND hwnd;
	HINSTANCE hInstance;

	HWND	hBase;
	int	active_page;
	std::vector <void*>	parts;
	std::vector <void*>	pages;

public:
	int AddPage();
	HWND CreateBase(HWND client_hwnd, HINSTANCE hInstance);
};
