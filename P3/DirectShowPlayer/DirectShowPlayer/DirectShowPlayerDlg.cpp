
// DirectShowPlayerDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "DirectShowPlayer.h"
#include "DirectShowPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDirectShowPlayerDlg-Dialogfeld

static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");

CDirectShowPlayerDlg::CDirectShowPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIRECTSHOWPLAYER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectShowPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectShowPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, &CDirectShowPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_PAUSE, &CDirectShowPlayerDlg::OnBnClickedPause)
	ON_BN_CLICKED(IDC_RESUME, &CDirectShowPlayerDlg::OnBnClickedResume)
	ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GetIt)
	ON_BN_CLICKED(IDC_STOP, &CDirectShowPlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_CLOSE, &CDirectShowPlayerDlg::OnBnClickedClose)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_VOLLBILD, &CDirectShowPlayerDlg::OnBnClickedVollbild)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_SELECTFILE, &CDirectShowPlayerDlg::OnBnClickedSelectfile)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDirectShowPlayerDlg-Meldungshandler

BOOL CDirectShowPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	DragAcceptFiles(TRUE);

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen
	CoInitialize(NULL);    // zur Initialisierung des COM-Interfaces

	SetTimer(1, 200, NULL);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDirectShowPlayerDlg::OnPaint()
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
HCURSOR CDirectShowPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDirectShowPlayerDlg::OnBnClickedPlay()
{
	if (m_FilePath.IsEmpty()) {
		AfxMessageBox(L"Bitte wählen Sie eine Datei aus.");
		return;
	}

	CleanUp();

	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&pGraph);

	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void**)&pEvent);

	HRESULT hr = pGraph->RenderFile(m_FilePath, NULL);
	if (FAILED(hr)) {
		AfxMessageBox(L"Fehler beim Laden der Datei.");
		return;
	}

	pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin);
	pGraph->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);

	if (pSeek->IsFormatSupported(&TIME_FORMAT_MEDIA_TIME) == S_OK)
		pSeek->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
	else
		AfxMessageBox(L"Zeitformat wird nicht unterstützt");

	if (pSeek) {
		REFERENCE_TIME d;
		pSeek->GetDuration(&d);
		CSliderCtrl* sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
		sl->SetRange(0, (int)(d / 1000000));
		sl->SetPos(0);
	}

	pVidWin->put_Owner((OAHWND)GetSafeHwnd());
	pVidWin->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
	pVidWin->put_Visible(OATRUE);

	pVidWin->SetWindowPosition(10, 10, 500, 300);
	pVidWin->put_MessageDrain((OAHWND)GetSafeHwnd());
	pEvent->SetNotifyWindow((OAHWND)GetSafeHwnd(), WM_GRAPHNOTIFY, 0);

	pMediaControl->Run();
	long evCode;
}


LRESULT CDirectShowPlayerDlg::GetIt(WPARAM wparam, LPARAM lparam) {
	long evCode;
	LONG_PTR param1, param2;
	while ((pEvent != NULL) && SUCCEEDED(pEvent->GetEvent(&evCode, &param1, &param2, 0))) {
		pEvent->FreeEventParams(evCode, param1, param2);
		switch (evCode) {
		case EC_COMPLETE:
		case EC_USERABORT:
			CleanUp(); return 0;
		}
	}
	return 0;
}

void CDirectShowPlayerDlg::CleanUp() { 
	if (pVidWin) { pVidWin->put_Visible(OAFALSE); 
		pVidWin->put_Owner(NULL); 
		pVidWin->Release(); 
		pVidWin = NULL; 
	} 

	if (pSeek) { 
		pSeek->Release(); 
		pSeek = NULL; 
	}

	if (pMediaControl) { 
		pMediaControl->Release(); 
		pMediaControl = NULL; 
	} 
	
	if (pEvent) { 
		pEvent->Release(); 
		pEvent = NULL; 
	} 
	
	/*if (pGraph) {
		Vollbild(false);
		pGraph = NULL;
	}*/

	if (pGraph) { 
		pGraph->Release();
		pGraph = NULL; 
	}

	//CoUninitialize(); 
}

void CDirectShowPlayerDlg::OnBnClickedPause()
{
	if (pMediaControl != 0) 
		pMediaControl->Pause(); 
}


void CDirectShowPlayerDlg::OnBnClickedResume()
{
	if (pMediaControl != 0) 
		pMediaControl->Run(); 
}


void CDirectShowPlayerDlg::OnBnClickedStop()
{
	if (pMediaControl != 0) { 
		pMediaControl->Stop(); 
		CleanUp(); 
	}
}


void CDirectShowPlayerDlg::OnBnClickedClose()
{
	CleanUp(); 
	CDialogEx::OnClose(); 
}


void CDirectShowPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (pSeek) {
		REFERENCE_TIME rtTotal, rtNow = 0; CString s;
		pSeek->GetDuration(&rtTotal);
		pSeek->GetCurrentPosition(&rtNow);
		s.Format(L"Abspielvorgang: %02d:%02d (%d%%)",
			(int)((rtNow / 10000000L) / 60),		// min 
			(int)((rtNow / 10000000L) % 60),		// sek 
			(int)((rtNow * 100) / rtTotal));		// Prozent 
		GetDlgItem(IDC_STATUS)->SetWindowText(s);

		((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos((int)(rtNow / 1000000));

	} else {
		GetDlgItem(IDC_STATUS)->SetWindowText(L"Abspielvorgang: 00:00 (0%)");
		((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos(0);
	}
	CDialog::OnTimer(nIDEvent);
}


void CDirectShowPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* sl1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER); 
	if ((pSeek) && ((void*)sl1 == (void*)pScrollBar)) { 
		REFERENCE_TIME pos = (REFERENCE_TIME)sl1->GetPos() * 1000000; 
		pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning); 
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDirectShowPlayerDlg::OnBnClickedVollbild()
{
	Vollbild(true);
}

void CDirectShowPlayerDlg::Vollbild(bool v) { 
	if (pGraph) { 
		IVideoWindow* pVidWin1 = NULL; 
		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin1); 
		pVidWin1->put_FullScreenMode(v ? OATRUE : OAFALSE); 
		pVidWin1->Release();
	} 
}

void CDirectShowPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	Vollbild(false);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDirectShowPlayerDlg::OnBnClickedSelectfile()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, L"Video Files (*.mpg;*.avi;*.mp4)|*.mpg;*.avi;*.mp4|All Files (*.*)|*.*||");
	if (dlg.DoModal() == IDOK)
	{
		m_FilePath = dlg.GetPathName(); // Speichere den ausgewählten Dateipfad
		OnBnClickedPlay(); // Rufe die Play-Methode auf
	}
}

void CDirectShowPlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	WCHAR szFileName[MAX_PATH];
	DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH); // Nur die erste Datei verarbeiten
	DragFinish(hDropInfo);

	m_FilePath = szFileName; // Speichere den Dateipfad
	OnBnClickedPlay(); // Rufe die Play-Methode auf
}
