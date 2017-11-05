// oBon.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

 	// TODO: �����ɃR�[�h��}�����Ă��������B
	NodeVar	node ;
		
	node = lpCmdLine;
	CmdOpt	*opt = new CmdOpt();

	if (opt->IsVersion())
	{
		// version �\��.
	}
	if (opt->IsHelp())
	{
		// Help �\��.
	}

	if (opt->IsGUI())
	{
		// GUI �ŋN��.
		ObonApp	*pApp = new ObonApp(hInstance, nCmdShow);
		pApp->Init();
		delete pApp;
	}
	else
	{
		// CUI �ŋN��.
	}

//	return (int)msg.wParam;
	return 0;
}
