
// PraktikumDS.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CPraktikumDSApp:
// Siehe PraktikumDS.cpp für die Implementierung dieser Klasse
//

class CPraktikumDSApp : public CWinApp
{
public:
	CPraktikumDSApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CPraktikumDSApp theApp;
