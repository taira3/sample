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

	// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
	static LRESULT CALLBACK	WndProcWrap(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	bool	OnDrop(WPARAM wp);
	bool	wakeUpSomeone(TCHAR *filePath);

#define MAX_LOADSTRING 100

	// �O���[�o���ϐ�:
	HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
	TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��
	int		nCmdShow;

	HINSTANCE hInstance;

	// jhone_doe

};

#endif // 0
