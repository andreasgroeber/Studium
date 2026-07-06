
// DirectShowPrakDlg.h: Headerdatei
//

#pragma once


// CDirectShowPrakDlg-Dialogfeld
class CDirectShowPrakDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectShowPrakDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTSHOWPRAK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	IGraphBuilder* pGraph; // ein Zeiger auf das COM-Interface
	IMediaControl* pMediaControl;
	IMediaEventEx* pEvent;
	IVideoWindow* pVidWin = NULL;
	IMediaSeeking* pSeek = NULL;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	void CleanUp();
	void Vollbild(bool v);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedResume();
	afx_msg LRESULT GetIt(WPARAM wparam, LPARAM lparam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedVollbild();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedChangefile();
};
