// BonDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "bonrt.h"
#include "bonfw.h"
#include "DebugLog.h"
#include "EasterEgg.h"


// CBonDlg �_�C�A���O
class CBonDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CBonDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_BON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	BonRT *m_bonRT;
	BonFW *m_bonFW;
	DebugLog	*m_log ;
	EasterEgg	*m_ee ;
	DebugLog	*m_dbg ;

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDestroy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
