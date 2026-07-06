
// DirectShowPrakDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "DirectShowPrak.h"
#include "DirectShowPrakDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectShowPrakDlg-Dialogfeld


static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");


CDirectShowPrakDlg::CDirectShowPrakDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTSHOWPRAK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectShowPrakDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectShowPrakDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Play, &CDirectShowPrakDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_Pause, &CDirectShowPrakDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_Resume, &CDirectShowPrakDlg::OnBnClickedResume)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_Vollbild, &CDirectShowPrakDlg::OnBnClickedVollbild)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_Stop, &CDirectShowPrakDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_Changefile, &CDirectShowPrakDlg::OnBnClickedChangefile)
END_MESSAGE_MAP()


// CDirectShowPrakDlg-Meldungshandler

BOOL CDirectShowPrakDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
	SetTimer(1, 200, NULL);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectShowPrakDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CDirectShowPrakDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectShowPrakDlg::OnBnClickedPlay()
{
	/* CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void**)&pGraph);

	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent); */

	// pGraph->RenderFile(L"testmp4.mp4", NULL);
	
	if (pGraph == NULL) //check auf gütlige datei
	{
		AfxMessageBox(L"Kein gueltiges File Ausgewaehlt!");
		return;
	}

	// Zeitformat 100 Nanosekunden
	if (pSeek->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME) == S_OK)
		pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	else
		AfxMessageBox(L"Zeitformat wird nicht unterstützt");


	if (pSeek) {
		REFERENCE_TIME d;
		pSeek->GetDuration(&d);
		CSliderCtrl* sl;
		sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
		sl->SetRange(0, (int)(d / 1000000)); sl->SetPos(0);
	}

	pVidWin->put_Owner((OAHWND)GetSafeHwnd());
	pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	pVidWin->put_Visible(OATRUE);

	pVidWin->SetWindowPosition(10, 70, 300, 200);

	// Nachrichtenbehandlung (Maus, Keyboard)
	pVidWin->put_MessageDrain((OAHWND)GetSafeHwnd());


	pEvent->SetNotifyWindow((OAHWND)GetSafeHwnd(), WM_GRAPHNOTIFY, 0);	

	pMediaControl->Run(); long evCode;
	
/*	pEvent->WaitForCompletion(INFINITE, &evCode);

	pVidWin->put_Visible(OAFALSE);
	pVidWin->put_Owner(NULL);
	pVidWin->Release();
	
	
	pMediaControl->Release();
	pEvent->Release();
	pGraph->Release();  
	
	*/
}


LRESULT CDirectShowPrakDlg::GetIt(WPARAM wparam, LPARAM lparam) {								// In Vorlesungs-Video LONG CDircetShowPrak ... 
	long evCode, param1, param2; HRESULT hr;
	while (SUCCEEDED(pEvent->GetEvent(&evCode, (LONG_PTR*)&param1, (LONG_PTR*)&param2, 0))) {
		pEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
		case EC_USERABORT:
			CleanUp(); return 0;
		}
	}
	return 0;
}

void CDirectShowPrakDlg::CleanUp() {
	if(pGraph) {
	
	Vollbild(false);
	pVidWin->put_Visible(OAFALSE);
	pVidWin->put_Owner(NULL);
	pMediaControl->Release();
	pVidWin->Release();
	pEvent->Release();
	pGraph->Release();
	pMediaControl = 0; pVidWin = 0; pSeek = 0;
	pEvent = 0; pGraph = 0; 
	//CoUnitialize(); 
	}
}


void CDirectShowPrakDlg::OnBnClickedPause()
{
	if (pMediaControl != 0) {
		pMediaControl->Pause();
	}
	
}


void CDirectShowPrakDlg::OnBnClickedResume()
{
	if (pMediaControl != 0) {
		pMediaControl->Run();
	}
}


void CDirectShowPrakDlg::OnBnClickedStop()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	if (pMediaControl != 0) {
		pMediaControl->Stop(); CleanUp();
	}
}



void CDirectShowPrakDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	if (pSeek) {
		REFERENCE_TIME rtTotal, rtNow = 0; CString s;
		pSeek->GetDuration(&rtTotal);
		pSeek->GetCurrentPosition(&rtNow);
		s.Format(L"Abspielvorgang: %02d:%02d (%d%%)",
			(int)((rtNow / 10000000L) / 60), // min
			(int)((rtNow / 10000000L) % 60), // sek
			(int)((rtNow * 100) / rtTotal)); // Prozent
		GetDlgItem(IDC_Status)->SetWindowText(s);


		((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos((int)(rtNow / 1000000));
		CDialog::OnTimer(nIDEvent);
		if (rtTotal == rtNow) // not Lösung, funktioniert nicht ohne
		{	
			GetDlgItem(IDC_Status)->SetWindowText(L"Apspielvorgang: 00:00 (0%)");
			((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos(0);
			Vollbild(false);
		}
	}		
	/*else {
		GetDlgItem(IDC_Status)->SetWindowText(L"Apspielvorgang: 00:00 (0%)");
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos(0);
		Vollbild(false);
	} */

	CDialogEx::OnTimer(nIDEvent);
}


void CDirectShowPrakDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
		pMediaControl->Pause();
		CSliderCtrl* sl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
		if ((pSeek) && ((void*)sl1 == (void*)pScrollBar)) {
			REFERENCE_TIME pos = (REFERENCE_TIME)sl1->GetPos() * 1000000;
			pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning,
				NULL, AM_SEEKING_NoPositioning);
		}
		pMediaControl->Run();

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDirectShowPrakDlg::OnBnClickedVollbild()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	Vollbild(true);
}

void CDirectShowPrakDlg::Vollbild(bool v) {
	if (pGraph) {
		IVideoWindow* pVidWin1 = NULL;
		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin1);
		pVidWin1->put_FullScreenMode(v ? OATRUE : OAFALSE);
		pVidWin1->Release();
	}
}


void CDirectShowPrakDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.

	Vollbild(false);
	CDialogEx::OnLButtonDown(nFlags, point);
}




void CDirectShowPrakDlg::OnBnClickedChangefile()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.


	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
	IID_IGraphBuilder, (void**)&pGraph);

	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent); 

										//Dateiname bekommen
	LPCTSTR pszFilter =
		_T("test (*.mp4)|*.mp4|");
		_T("test (*.mp3)|*.mp3|");

		CFileDialog dlgFile(TRUE, _T("mp4"),NULL,OFN_FILEMUSTEXIST,pszFilter,AfxGetMainWnd());
		if (IDOK == dlgFile.DoModal())
		{
				// --> hier müsste Filpath abgespeichtert werden und in Renderfile eingefügt !!!
		}

	pGraph->RenderFile(L"testmp4.mp4", NULL);
		
	pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin);
	pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);
}
