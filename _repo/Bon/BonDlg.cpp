// BonDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Bon.h"
#include "BonDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
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


// CBonDlg �_�C�A���O




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


// CBonDlg ���b�Z�[�W �n���h��

BOOL CBonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// IDM_ABOUTBOX �́A�V�X�e�� �R�}���h�͈͓̔��ɂȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B
	m_bonFW = new BonFW();
	m_bonFW->load();

	m_log = new DebugLog();
	m_ee = new EasterEgg();
	m_dbg = new DebugLog();

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
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

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CBonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CBonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <fstream>
using namespace std;
//#include "yaml-cpp/yaml.h"


void CBonDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B

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

	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����܂��B
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
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	switch( pMsg->message )
	{
	case WM_KEYUP:
		TRACE( _T("WM_KEYUP: 0x%x\n"), pMsg->wParam );

		// 
		if( m_ee->AddCmd( pMsg->wParam ) )
		{
			// �C�x���g����.
			TRACE("Event=%d\n",m_ee->getEvent());
			m_dbg->setOutputConsole();
		}
		break;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
