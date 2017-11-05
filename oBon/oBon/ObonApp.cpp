#include "stdafx.h"
#include "ObonApp.h"
#include "oBon.h"
#include <shellapi.h>

#if 1
ObonApp::~ObonApp()
{
}

void	ObonApp::Init()
{
	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDC_OBON, szWindowClass, MAX_LOADSTRING);
	WNDCLASSEX wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProcWrap;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBON));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(GetSysColor(COLOR_MENU));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;

	ATOM a = RegisterClassEx(&wcex);

	// �A�v���P�[�V�����̏����������s���܂�:

	//	hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B
	
	HWND hWnd = CreateWindowEx(
		WS_EX_ACCEPTFILES,		//DWORD dwExStyle,
		szWindowClass,		//LPCTSTR lpClassName,
		_T("TestApp"),		//LPCTSTR lpWindowName,
		WS_OVERLAPPEDWINDOW, //DWORD dwStyle,
		CW_USEDEFAULT,		//int x,
		CW_USEDEFAULT,		//int y,
		CW_USEDEFAULT,		//int nWidth,
		CW_USEDEFAULT,		//int nHeight,
		NULL,				//HWND hWndParent,
		NULL,				//HMENU hMenu,
		hInstance,			//HINSTANCE hInstance,
		this				//LPVOID lpParam
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

	UnregisterClass(MAKEINTATOM(a), hInstance);

}

//
LRESULT CALLBACK	ObonApp::WndProcWrap(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	ObonApp *pThis = NULL;

	if (message == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (ObonApp*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
	}
	else
	{
		pThis = (ObonApp*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}

	return pThis ? pThis->WndProc(hWnd, message, wParam, lParam) : DefWindowProc(hWnd, message, wParam, lParam);
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
	case WM_INITDIALOG:
		//
		DragAcceptFiles(hWnd, TRUE);		// File DnD ����.
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

#endif // 0