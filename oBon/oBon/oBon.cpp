// oBon.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "oBon.h"
#include "ObonApp.h"
#include "CmdOpt.h"
#include "NodeVar.h"
#include <shellapi.h>




int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ここにコードを挿入してください。
	NodeVar	node ;
		
	node = lpCmdLine;
	CmdOpt	*opt = new CmdOpt();

	if (opt->IsVersion())
	{
		// version 表示.
	}
	if (opt->IsHelp())
	{
		// Help 表示.
	}

	if (opt->IsGUI())
	{
		// GUI で起動.
		ObonApp	*pApp = new ObonApp(hInstance, nCmdShow);
		pApp->Init();
		delete pApp;
	}
	else
	{
		// CUI で起動.
	}

//	return (int)msg.wParam;
	return 0;
}
