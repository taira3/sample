#pragma once

#include "resource.h"

#include "UXCore.h"
#include "EasterEgg.h"


class ObonApp
{
public:
	ObonApp(HINSTANCE v1, int v2);
	~ObonApp();

	void	Run();

	// このコード モジュールに含まれる関数の宣言を転送します:
	static LRESULT CALLBACK	WndProcProxy(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	bool	OnDrop(WPARAM wp);
	bool	wakeUpSomeone(TCHAR *filePath);

#define MAX_LOADSTRING 100

	// グローバル変数:
	HINSTANCE hInst;								// 現在のインターフェイス
	TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名
	int		nCmdShow;

	HINSTANCE hInstance;
	ATOM unique_class;

	HWND	hTab;

	UXCore	*ux = NULL;

	// jhone_doe

	EasterEgg	ee;
};
