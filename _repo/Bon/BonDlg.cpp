// BonDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "Bon.h"
#include "BonDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBonDlg ダイアログ




CBonDlg::CBonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBonDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBonDlg メッセージ ハンドラ

BOOL CBonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	m_bonFW = new BonFW();
	m_bonFW->load();

	m_log = new DebugLog();
	m_ee = new EasterEgg();
	m_dbg = new DebugLog();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CBonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CBonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CBonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <fstream>
using namespace std;
//#include "yaml-cpp/yaml.h"


void CBonDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。

	char FileName[MAX_PATH];
	int NameSize = sizeof(FileName);

	CStatic	*pMsg = (CStatic*)GetDlgItem(IDC_MSG);

	int FileNumber = DragQueryFileA(hDropInfo, 0xffffffff, FileName, NameSize);
	for( int i = 0 ; i < FileNumber ; i++ )
	{
		DragQueryFileA(hDropInfo, i, FileName, NameSize);

		m_log->Info("File=%s\n",FileName);
		cout << FileName << endl ;

		CString	msg ;
		pMsg->GetWindowText( msg );
		msg.Format(_T("File:%s\n"),CA2W(FileName));
		pMsg->SetWindowText( msg );
		
		if( m_bonFW->entry( string(FileName) ) )
		{
			msg += _T("Analyze....\n");
			pMsg->SetWindowText( msg );
			cout << "Analyze...." << endl ;

			BeginWaitCursor();
			m_bonFW->createWorkspace();
			bool res = m_bonFW->analyze();
			EndWaitCursor();
			if( res )
			{
				msg += _T("Success.");
				pMsg->SetWindowText( msg );
				cout << "Success." << endl ;
			}
			else
			{
				msg += _T("Error.");
				pMsg->SetWindowText( msg );
				cout << "Error." << endl ;
			}
		}
		else
		{
			msg += _T("Not Support.");
			pMsg->SetWindowText( msg );
			cout << "Not Support." << endl ;
		}
	}

	CDialog::OnDropFiles(hDropInfo);
}

void CBonDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ここにメッセージ ハンドラ コードを追加します。
	if( m_bonFW )
	{
		delete m_bonFW ;
	}
	if( m_log )
	{
		delete m_log ;
	}
	if( m_ee )
	{
		delete m_ee ;
	}
	if( m_dbg )
	{
		delete m_dbg ;
	}
}

BOOL CBonDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	switch( pMsg->message )
	{
	case WM_KEYUP:
		TRACE( _T("WM_KEYUP: 0x%x\n"), pMsg->wParam );

		// 
		if( m_ee->AddCmd( pMsg->wParam ) )
		{
			// イベント発生.
			TRACE("Event=%d\n",m_ee->getEvent());
			m_dbg->setOutputConsole();
		}
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
