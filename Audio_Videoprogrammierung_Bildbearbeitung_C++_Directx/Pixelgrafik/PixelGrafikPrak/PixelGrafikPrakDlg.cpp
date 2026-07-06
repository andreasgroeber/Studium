
// PixelGrafikPrakDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "PixelGrafikPrak.h"
#include "PixelGrafikPrakDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPixelGrafikPrakDlg-Dialogfeld



CPixelGrafikPrakDlg::CPixelGrafikPrakDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIXELGRAFIKPRAK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPixelGrafikPrakDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelGrafikPrakDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_But1, &CPixelGrafikPrakDlg::OnBnClickedBut1)
	ON_BN_CLICKED(IDC_But2, &CPixelGrafikPrakDlg::OnBnClickedBut2)
	ON_BN_CLICKED(IDC_But3, &CPixelGrafikPrakDlg::OnBnClickedBut3)
	ON_BN_CLICKED(IDC_But4, &CPixelGrafikPrakDlg::OnBnClickedBut4)
	ON_BN_CLICKED(IDC_But5, &CPixelGrafikPrakDlg::OnBnClickedBut5)
	ON_BN_CLICKED(IDC_But6, &CPixelGrafikPrakDlg::OnBnClickedBut6)
	ON_BN_CLICKED(IDC_But8, &CPixelGrafikPrakDlg::OnBnClickedBut8)
	ON_BN_CLICKED(IDC_But9, &CPixelGrafikPrakDlg::OnBnClickedBut9)
	ON_BN_CLICKED(IDC_But7, &CPixelGrafikPrakDlg::OnBnClickedBut7)
	ON_BN_CLICKED(IDC_But10, &CPixelGrafikPrakDlg::OnBnClickedBut10)
	ON_BN_CLICKED(IDC_But11, &CPixelGrafikPrakDlg::OnBnClickedBut11)
	ON_BN_CLICKED(IDC_But12, &CPixelGrafikPrakDlg::OnBnClickedBut12)
	ON_BN_CLICKED(IDC_But13, &CPixelGrafikPrakDlg::OnBnClickedBut13)
	ON_BN_CLICKED(IDC_But14, &CPixelGrafikPrakDlg::OnBnClickedBut14)
	ON_BN_CLICKED(IDC_But15, &CPixelGrafikPrakDlg::OnBnClickedBut15)
	ON_BN_CLICKED(IDC_But16, &CPixelGrafikPrakDlg::OnBnClickedBut16)
	ON_BN_CLICKED(IDC_But17, &CPixelGrafikPrakDlg::OnBnClickedBut17)
	ON_BN_CLICKED(IDC_But18, &CPixelGrafikPrakDlg::OnBnClickedBut18)
	ON_BN_CLICKED(IDC_But19, &CPixelGrafikPrakDlg::OnBnClickedBut19)
	ON_BN_CLICKED(IDC_But20, &CPixelGrafikPrakDlg::OnBnClickedBut20)
END_MESSAGE_MAP()


// CPixelGrafikPrakDlg-Meldungshandler

BOOL CPixelGrafikPrakDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	/*if (!m_dib.Load(L"bild.bmp")) {
		AfxMessageBox(L"blume.bmp ist keine bmp-Datei");
		OnCancel(); return FALSE;
	} */

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

 void CPixelGrafikPrakDlg::OnPaint()
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	if (IsIconic())
	{
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
		
		m_dib.Draw(&dc, 0, 0);

		CDialogEx::OnPaint(); 
	}
} 

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CPixelGrafikPrakDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





/* void CPixelGrafikPrakDlg::OnMouseMove(UINT nFlags, CPoint point)								Schwarz zeichnen on mouse move
{

	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	CClientDC dc(this);
	BYTE* p = (BYTE*)m_dib.GetPixelAddress(point.x, point.y);
	if (p) {
		p[0] = p[1] = p[2] = 0;
		m_dib.Draw(&dc,0,0);
		m_dib.Save(L"test.bmp");
	}
	CDialogEx::OnMouseMove(nFlags, point);
} */


void CPixelGrafikPrakDlg::OnBnClickedBut18() //bild zeigen
{

	m_dib.Load(L"bild.bmp");
	RedrawWindow();
} 




void CPixelGrafikPrakDlg::OnBnClickedBut1()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	m_dib.brighten(10);
	RedrawWindow();
}




void CPixelGrafikPrakDlg::OnBnClickedBut2()
{
	m_dib.negative();
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut3()
{
	m_dib.darken(10);
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut4()
{
	m_dib.grey();
	RedrawWindow();
}



void CPixelGrafikPrakDlg::OnBnClickedBut5()								//draw histogramm per button!
{
		float h[256] = { 0.f }; int x = 10, y = 105;							
		CClientDC dc(this);
		m_dib.histogramm(h, 20.f);
		dc.MoveTo(x, y); dc.LineTo(x + 255 + 2, y); // Rahmen zeichnen
		dc.LineTo(x + 255 + 2, y - 101); dc.LineTo(x, y - 101); dc.LineTo(x, y);
		CPen p(PS_SOLID, 1, RGB(255, 255, 0)); dc.SelectObject(&p);
		for (int i = 0; i < 255; i++) { // Histogramm zeichnen
			dc.MoveTo(x + i + 1, y - 1);
			dc.LineTo(x + i + 1, y - 1 - (100 * h[i]));
	}
}



void CPixelGrafikPrakDlg::OnBnClickedBut6()   //kontrast
{
	m_dib.contrast(1.25);
	RedrawWindow();
}

void CPixelGrafikPrakDlg::OnBnClickedBut7()  //blending mit Slider noch zu machen !
{
	m_dib2.Load(L"bild.bmp");
	m_dib2.flip('v');
	m_dib.blending(m_dib,m_dib2,50);
	RedrawWindow();
}



void CPixelGrafikPrakDlg::OnBnClickedBut8()
{
	m_dib.rgb('r');
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut9()
{
	m_dib.rgb('g');
	RedrawWindow();
}




void CPixelGrafikPrakDlg::OnBnClickedBut10()
{
	m_dib.rgb('b');
	RedrawWindow();
}




void CPixelGrafikPrakDlg::OnBnClickedBut11()  //schärfe
{
	int f = 1;
	int sharpen_matrix[9] = { -1,-1,-1,-1,9,-1,-1,-1,-1};
	m_dib.matrix(sharpen_matrix, 1, f,0);                    //matrix, size, koeffizient,offset
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut12() //unschärfe
{
	int f = 97;
	int soften_matrix[9] = { 6,12,6,12,25,12,6,12,6 };
	m_dib.matrix(soften_matrix, 1, f, 0);
	RedrawWindow();
}




void CPixelGrafikPrakDlg::OnBnClickedBut13() // emboss
{
	int f = 1;
	int emboss_matrix[9] = { -1,0,0,0,0,0,0,0,1 };
	m_dib.matrix(emboss_matrix, 1, f, 127);
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut14() // kantenerkennung
{
	int f = 1;
	int edge_matrix[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 };
	m_dib.matrix(edge_matrix, 1, f, 0);
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut15()
{
	int f = 1;
	int relief_matrix[9] = { -2,-1,0,-1,1,1,0,1,2 };
	m_dib.matrix(relief_matrix, 1, f, 0);
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut16() //fliping
{	
	m_dib.flip('h');
	RedrawWindow();
}


void CPixelGrafikPrakDlg::OnBnClickedBut17()
{
	m_dib.flip('v');
	RedrawWindow();
}



void CPixelGrafikPrakDlg::OnBnClickedBut19() //jpeg
{
	m_dib.SaveJpeg(L"testbildJPEG.jpg", 90);
}


void CPixelGrafikPrakDlg::OnBnClickedBut20()
{
	m_dib.LoadJpeg(L"testbildJPEG.jpg");
	RedrawWindow();
}
