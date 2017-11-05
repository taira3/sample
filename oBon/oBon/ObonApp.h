#pragma once

#include "resource.h"

#if 1
class ObonApp
{
public:
	ObonApp(HINSTANCE v1, int v2) {
		hInstance = v1;
		nCmdShow = v2;
	}
	~ObonApp();

	void	Init();
///	ATOM				MyRegisterClass(HINSTANCE hInstance);

	// このコード モジュールに含まれる関数の宣言を転送します:
	static LRESULT CALLBACK	WndProcWrap(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	bool	OnDrop(WPARAM wp);
	bool	wakeUpSomeone(TCHAR *filePath);

#define MAX_LOADSTRING 100

	// グローバル変数:
	HINSTANCE hInst;								// 現在のインターフェイス
	TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名
	int		nCmdShow;

	HINSTANCE hInstance;

	// jhone_doe

};

#endif // 0
