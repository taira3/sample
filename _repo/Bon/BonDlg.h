// BonDlg.h : ヘッダー ファイル
//

#pragma once
#include "bonrt.h"
#include "bonfw.h"
#include "DebugLog.h"
#include "EasterEgg.h"


// CBonDlg ダイアログ
class CBonDlg : public CDialog
{
// コンストラクション
public:
	CBonDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_BON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
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
