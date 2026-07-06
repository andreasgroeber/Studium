
// PixelGrafikPrak.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CPixelGrafikPrakApp:
// Siehe PixelGrafikPrak.cpp für die Implementierung dieser Klasse
//

class CPixelGrafikPrakApp : public CWinApp
{
public:
	CPixelGrafikPrakApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CPixelGrafikPrakApp theApp;
