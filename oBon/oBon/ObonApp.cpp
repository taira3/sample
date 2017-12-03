#include "stdafx.h"
#include "ObonApp.h"
#include "oBon.h"
#include <shellapi.h>
#include <commctrl.h>

ObonApp::ObonApp(HINSTANCE v1, int v2)
{
	hInstance = v1;
	nCmdShow = v2;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDC_OBON, szWindowClass, MAX_LOADSTRING);

	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProcProxy;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENU));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;

	unique_class = RegisterClassEx(&wcex);
}

ObonApp::~ObonApp()
{
	UnregisterClass(MAKEINTATOM(unique_class), hInstance);
}

//
void	ObonApp::Run()
{
	HWND hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES,		// dwExStyle,
		szWindowClass,			// lpClassName,
		_T("TestApp"),			// lpWindowName,
		WS_OVERLAPPEDWINDOW,	// dwStyle,
		CW_USEDEFAULT,			// x,
		CW_USEDEFAULT,			// y,
		CW_USEDEFAULT,			// nWidth,
		CW_USEDEFAULT,			// nHeight,
		NULL,					// hWndParent,
		NULL,					// hMenu,
		hInstance,				// hInstance,
		this					// lpParam
	);

	if (!hWnd)
	{
		return;// FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���C�� ���b�Z�[�W ���[�v:
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	DestroyWindow(hWnd);
}

//
LRESULT CALLBACK	ObonApp::WndProcProxy(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ObonApp *pThis = NULL;

	// WndProc()��Class���ň����ꍇ�Astatic��Wrapper�֐�(�{�֐�)��   .
	// CreateWindowsEX()�̈����œn���ꂽthis���AWM_NCCREATE��WM_CREATE�� .
	// WindowLongPtr�ɐݒ�/�Q�Ƃ�MFP��ATL�ł��̂鉤���A�v���[�`�炵�� .
	// https://msdn.microsoft.com/ja-jp/library/windows/desktop/ff381400(v=vs.85).aspx .
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT *pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<ObonApp*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
	}
	else
	{
		pThis = reinterpret_cast<ObonApp*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	return pThis ?
		pThis->WndProc(hWnd, message, wParam, lParam) : 
		DefWindowProc(hWnd, message, wParam, lParam) ;
}

//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
//
//
LRESULT CALLBACK ObonApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		ux = new UXCore(hWnd, ((LPCREATESTRUCT)lParam)->hInstance);
		break;


	case WM_INITDIALOG:
		//
		//DragAcceptFiles(hWnd, TRUE);		// File DnD ����.
		break;

	case WM_KEYUP:
		//
		break;

	case WM_LBUTTONDBLCLK:
		//
		break;

	case WM_LBUTTONUP:
		//
		ux->AddPage();
		break;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

			//
		case IDOK:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �`��R�[�h�������ɒǉ����Ă�������...
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
bool	ObonApp::OnDrop(WPARAM wp)
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

// �t�@�C���ɑΉ������u�N���v���N����.
bool	ObonApp::wakeUpSomeone(TCHAR *filePath)
{
	OutputDebugString(filePath);
	return false;
}
