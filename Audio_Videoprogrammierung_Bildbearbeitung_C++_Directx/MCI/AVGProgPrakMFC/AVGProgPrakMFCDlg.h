
// AVGProgPrakMFCDlg.h: Headerdatei
//

#pragma once

#include "CMCIObject.h"


// CAVGProgPrakMFCDlg-Dialogfeld
class CAVGProgPrakMFCDlg : public CDialogEx
{
// Konstruktion
public:
	CAVGProgPrakMFCDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AVGPROGPRAKMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	CMCIObject mci;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void Change_Track_Tracklist();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
