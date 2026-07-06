
// AVGProgPrakMFCDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "AVGProgPrakMFC.h"
#include "AVGProgPrakMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAVGProgPrakMFCDlg-Dialogfeld



CAVGProgPrakMFCDlg::CAVGProgPrakMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AVGPROGPRAKMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVGProgPrakMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAVGProgPrakMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CAVGProgPrakMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CAVGProgPrakMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CAVGProgPrakMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CAVGProgPrakMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAVGProgPrakMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CAVGProgPrakMFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAVGProgPrakMFCDlg::OnBnClickedButton7)
	ON_LBN_SELCHANGE(IDC_Tracklist, &CAVGProgPrakMFCDlg::Change_Track_Tracklist)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAVGProgPrakMFCDlg-Meldungshandler

BOOL CAVGProgPrakMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	SetTimer(1, 200, 0); //<------------------------------------
	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CAVGProgPrakMFCDlg::OnPaint()
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
HCURSOR CAVGProgPrakMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*----------------------------Buttons-Grundfunktionen---------------------------------------------------------*/

void CAVGProgPrakMFCDlg::OnBnClickedButton2() //PLAY
{
	mci.Play();
}

void CAVGProgPrakMFCDlg::OnBnClickedButton4() //EXIT
{
	this->DestroyWindow(); // minimieren mit this->CloseWindow();
}


void CAVGProgPrakMFCDlg::OnBnClickedButton1() //PAUSE
{
	mci.Pause();
}


void CAVGProgPrakMFCDlg::OnBnClickedButton3() //CANCEL
{
	mci.Close();
}

/*----------------------------------------Buttons-Medium-----------------------------------------------------------*/


void CAVGProgPrakMFCDlg::OnBnClickedButton5() // mp3
{
	mci.OpenFile(L"U:/AVG_Praktikum/AVGProg_PrakMCI/Testvideo/testmp3.mp3");
	mci.Play();
}



void CAVGProgPrakMFCDlg::OnBnClickedButton6() //mpeg
{
	{					/* alternative zur r-Methode <--- mci.SetVideoPosition(GetSafeHwnd(), CRect(50, 100, 400, 225)); */
		CRect r;
		GetDlgItem(IDC_Videobox)->GetWindowRect(r);		//Abfrage der Größe Box --> Weitergabe/Speicherung in Objekt-r  
		ScreenToClient(r);
		mci.OpenFile(L"U:/AVG_Praktikum/AVGProg_PrakMCI/Testvideo/testmpg.mpeg");
		mci.SetVideoPosition(GetSafeHwnd(),
			CRect(r.left, r.top, r.Width(), r.Height()));
		mci.Play();
	}
}



void CAVGProgPrakMFCDlg::OnBnClickedButton7() //cd
{
	BYTE tracks;
	mci.OpenAudioCD(0, tracks);

	BYTE min, sek, frame;
	((CListBox*)GetDlgItem(IDC_Tracklist))->ResetContent();
	for (int i = 1; i <= tracks; i++) 
	{
		mci.GetTrackLength(i, min, sek, frame);
		CString temp; // z.B.Eintrag in eine ListBox : -)
		temp.Format(L"[%02d] %02d:%02d", i, min, sek);
		((CListBox*)GetDlgItem(IDC_Tracklist))->AddString(temp);
	}
	mci.Play();
}

/*------------------------------------------Timer/Tracklist--------------------------------------------------------*/

void CAVGProgPrakMFCDlg::Change_Track_Tracklist()
{
	mci.TMSFSeek(((CListBox*)GetDlgItem(IDC_Tracklist))->GetCurSel() + 1, 0, 0, 0);
	mci.Play();
}




void CAVGProgPrakMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString str;
	unsigned char t, m, s, f;
	mci.GetTMSFPosition(t, m, s, f);
	str.Format(L"[%02d] %02d:%02d", t, m, s);
	SetDlgItemText(IDC_Timetrack, str);
	CDialog::OnTimer(nIDEvent);

	CDialogEx::OnTimer(nIDEvent);
} 



/*------------------------------------------Prozentanzeige-----------------------------------------------------------*/


 /*void CAVGProgPrakMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString str;
	unsigned char m, s, f;
	mci.GetTrackLength(00, m, s, f);
	str.Format(L"[%02d] %02d:%02d", 00, 30, 29); // stimmt soweit ---> Returnwerte anpassen für Prozente Zeit in Sekunden oder Millisekunden Umrechnen Currentlength/maxlength*100 -> Good to go
	SetDlgItemText(IDC_Timetrackprtc, str);
	CDialog::OnTimer(nIDEvent);

	CDialogEx::OnTimer(nIDEvent);
} */



