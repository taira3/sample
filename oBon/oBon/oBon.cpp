// oBon.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "oBon.h"
#include <shellapi.h>

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM				MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
bool	OnDrop(WPARAM wp);
bool	wakeUpSomeone(TCHAR *filePath);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ここにコードを挿入してください。

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDC_OBON, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:

	hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

	HWND hWnd = CreateDialog(hInstance , MAKEINTRESOURCE(IDD_MAIN) ,0 ,(DLGPROC)WndProc);
	if (!hWnd)
	{
	  return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メイン メッセージ ループ:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!IsDialogMessage(hWnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			switch (msg.message)
			{
			case WM_KEYUP:
				PostMessage(hWnd, WM_DESTROY,0,0);
				break;
			}
		}
	}

	return (int) msg.wParam;
}

//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
//  コメント:
//
//    この関数および使い方は、'RegisterClassEx' 関数が追加された
//    Windows 95 より前の Win32 システムと互換させる場合にのみ必要です。
//    アプリケーションが、関連付けられた
//    正しい形式の小さいアイコンを取得できるようにするには、
//    この関数を呼び出してください。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= DLGWINDOWEXTRA;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBON));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENU));
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;

	return RegisterClassEx(&wcex);
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:  メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_INITDIALOG:
		//
		DragAcceptFiles(hWnd, TRUE);		// File DnD 許可.
		break;

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
		// 選択されたメニューの解析:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case IDOK:
			SendMessage(hWnd , WM_CLOSE , 0 , 0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 描画コードをここに追加してください...
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_DROPFILES:
		OnDrop(wParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 
bool	OnDrop(WPARAM wp)
{
	HDROP	hDrop = (HDROP)wp;
	UINT	uFileNo = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	TCHAR	szFileName[MAX_PATH];

	for (int i = 0; i < (int)uFileNo; i++)
	{
		DragQueryFile(hDrop, i, szFileName, sizeof(szFileName));
		wakeUpSomeone(szFileName);

	}
	DragFinish(hDrop);

	return false;
}

// ファイルに対応した「誰か」を起こす.
bool	wakeUpSomeone(TCHAR *filePath)
{
	OutputDebugString(filePath);
	return false;
}
