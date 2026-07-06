// PixelGrafikPrakDlg.h: Headerdatei
//

#pragma once
#include "CDIB.h"

// CPixelGrafikPrakDlg-Dialogfeld
class CPixelGrafikPrakDlg : public CDialogEx
{
// Konstruktion
public:
	CPixelGrafikPrakDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIXELGRAFIKPRAK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	CDIB m_dib;
	CDIB m_dib2;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBut1();
	afx_msg void OnBnClickedBut2();
	afx_msg void OnBnClickedBut3();
	afx_msg void OnBnClickedBut4();
	afx_msg void OnBnClickedBut5();
	afx_msg void OnBnClickedBut6();
	afx_msg void OnBnClickedBut8();
	afx_msg void OnBnClickedBut9();
	afx_msg void OnBnClickedBut7();
	afx_msg void OnBnClickedBut10();
	afx_msg void OnBnClickedBut11();
	afx_msg void OnBnClickedBut12();
	afx_msg void OnBnClickedBut13();
	afx_msg void OnBnClickedBut14();
	afx_msg void OnBnClickedBut15();
	afx_msg void OnBnClickedBut16();
	afx_msg void OnBnClickedBut17();
	afx_msg void OnBnClickedBut18();
	afx_msg void OnBnClickedBut19();
	afx_msg void OnBnClickedBut20();
};
