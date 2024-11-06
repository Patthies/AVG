
// DSound.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CDSoundApp:
// Siehe DSound.cpp für die Implementierung dieser Klasse
//

class CDSoundApp : public CWinApp
{
public:
	CDSoundApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CDSoundApp theApp;
