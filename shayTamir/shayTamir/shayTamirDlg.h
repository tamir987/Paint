
// shayTamirDlg.h : header file
//

#pragma once
#include "PictureWindow.h"
#include "afxwin.h"


// CshayTamirDlg dialog
class CshayTamirDlg : public CDialogEx
{
// Construction
public:
	CPictureWindow objPictureWindow;
	CshayTamirDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHAYTAMIR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton startButton;
};
