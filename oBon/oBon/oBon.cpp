// oBon.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "oBon.h"
#include <shellapi.h>


void test()
{
	NodeVar	a;

	try
	{
		a = "abc";
		a = "������";

		a = _T("abc");
		a = _T("������");

	}
	catch (const std::exception&d)
	{
		printf("%s\n", d.what());
	}

}

//
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);

	test();

	// ---- �O���� ----

	// 
	NodeVar	node = lpCmdLine;
	
	CmdOpt	*opt = new CmdOpt(node);

	//
	if (opt->IsVersion())
	{
		// version �\��.
	}

	//
	if (opt->IsHelp())
	{
		// Help �\��.
	}

	// ---- �{�� ----

	int result = opt->IsGUI() ? 
		RunGuiMode(hInstance, nCmdShow, opt) : 
		RunCuiMode(hInstance, nCmdShow, opt) ;

	// ---- ��n�� ----

	delete opt;

	return result;
}

//
int RunGuiMode(HINSTANCE hInstance, int nCmdShow, CmdOpt *opt)
{
	ObonApp	*pApp = new ObonApp(hInstance, nCmdShow);
	pApp->Run();
	delete pApp;

	return 0;
}

int RunCuiMode(HINSTANCE hInstance, int nCmdShow, CmdOpt *opt)
{
	ObonApp	*pApp = new ObonApp(hInstance, nCmdShow);
	pApp->Run();
	delete pApp;

	return 0;
}

