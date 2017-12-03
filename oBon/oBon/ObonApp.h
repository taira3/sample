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

	// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
	static LRESULT CALLBACK	WndProcProxy(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	bool	OnDrop(WPARAM wp);
	bool	wakeUpSomeone(TCHAR *filePath);

#define MAX_LOADSTRING 100

	// �O���[�o���ϐ�:
	HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
	TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��
	int		nCmdShow;

	HINSTANCE hInstance;
	ATOM unique_class;

	HWND	hTab;

	UXCore	*ux = NULL;

	// jhone_doe

	EasterEgg	ee;
};
