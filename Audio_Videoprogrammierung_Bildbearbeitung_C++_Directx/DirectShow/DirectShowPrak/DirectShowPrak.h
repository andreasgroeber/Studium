
// DirectShowPrak.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDirectShowPrakApp:
// Siehe DirectShowPrak.cpp für die Implementierung dieser Klasse
//

class CDirectShowPrakApp : public CWinApp
{
public:
	CDirectShowPrakApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDirectShowPrakApp theApp;
