// HexBinDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "ValidatingEdit.h"


// CHexBinDlg dialog
class CHexBinDlg : public CDialog
{
// Construction
public:
	CHexBinDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HEXBIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CFont monoFont;
	int update_cnt;
	HICON m_hIcon;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeDecimal();
public:
//	afx_msg void OnBnClickedQuit();
protected:
	CValidatingEdit m_BinEdit;
	CValidatingEdit m_DecEdit;
	CValidatingEdit m_HexEdit;
	CValidatingEdit m_OctalEdit;
public:
	afx_msg void OnEnChangeHexedit();
public:
	afx_msg void OnEnChangeOctaledit();
public:
	afx_msg void OnEnChangeBinedit();
public:
	CEdit m_BinText;
};

void sprintb(char *s, unsigned __int64 n);