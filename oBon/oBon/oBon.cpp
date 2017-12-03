// oBon.cpp : アプリケーションのエントリ ポイントを定義します。
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
		a = "あいう";

		a = _T("abc");
		a = _T("あいう");

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

	// ---- 前準備 ----

	// 
	NodeVar	node = lpCmdLine;
	
	CmdOpt	*opt = new CmdOpt(node);

	//
	if (opt->IsVersion())
	{
		// version 表示.
	}

	//
	if (opt->IsHelp())
	{
		// Help 表示.
	}

	// ---- 本題 ----

	int result = opt->IsGUI() ? 
		RunGuiMode(hInstance, nCmdShow, opt) : 
		RunCuiMode(hInstance, nCmdShow, opt) ;

	// ---- 後始末 ----

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

