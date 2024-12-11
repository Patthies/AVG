// CDirectShowPlayer.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "DirectShowPlayer.h"
#include "CDirectShowPlayer.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDirectShowPlayer-Dialogfeld

static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");

CDirectShowPlayer::CDirectShowPlayer(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIRECTSHOWPLAYER_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDirectShowPlayer::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDirectShowPlayer, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_PLAY, &CDirectShowPlayer::OnBnClickedPlay)
    ON_BN_CLICKED(IDC_PAUSE, &CDirectShowPlayer::OnBnClickedPause)
    ON_BN_CLICKED(IDC_RESUME, &CDirectShowPlayer::OnBnClickedResume)
    ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GetIt)
    ON_BN_CLICKED(IDC_STOP, &CDirectShowPlayer::OnBnClickedStop)
    ON_BN_CLICKED(IDC_CLOSE, &CDirectShowPlayer::OnBnClickedClose)
    ON_WM_TIMER()
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_VOLLBILD, &CDirectShowPlayer::OnBnClickedVollbild)
    ON_WM_LBUTTONDOWN()
    ON_BN_CLICKED(IDC_SELECTFILE, &CDirectShowPlayer::OnBnClickedSelectfile)
    ON_WM_DROPFILES()
END_MESSAGE_MAP()

BOOL CDirectShowPlayer::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    DragAcceptFiles(TRUE);

    SetIcon(m_hIcon, TRUE); // Großes Symbol
    SetIcon(m_hIcon, FALSE); // Kleines Symbol

    CoInitialize(NULL); // Initialisierung des COM-Interfaces

    SetTimer(1, 200, NULL);

    return TRUE; // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CDirectShowPlayer::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this);

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR CDirectShowPlayer::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CDirectShowPlayer::OnBnClickedPlay()
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
}

LRESULT CDirectShowPlayer::GetIt(WPARAM wparam, LPARAM lparam)
{
    long evCode;
    LONG_PTR param1, param2;
    while ((pEvent != NULL) && SUCCEEDED(pEvent->GetEvent(&evCode, &param1, &param2, 0))) {
        pEvent->FreeEventParams(evCode, param1, param2);
        switch (evCode) {
        case EC_COMPLETE:
        case EC_USERABORT:
            CleanUp();
            return 0;
        }
    }
    return 0;
}

void CDirectShowPlayer::CleanUp()
{
    if (pVidWin) { pVidWin->put_Visible(OAFALSE); pVidWin->put_Owner(NULL); pVidWin->Release(); pVidWin = NULL; }
    if (pSeek) { pSeek->Release(); pSeek = NULL; }
    if (pMediaControl) { pMediaControl->Release(); pMediaControl = NULL; }
    if (pEvent) { pEvent->Release(); pEvent = NULL; }
    if (pGraph) { pGraph->Release(); pGraph = NULL; }
}

void CDirectShowPlayer::OnBnClickedPause()
{
    if (pMediaControl) pMediaControl->Pause();
}

void CDirectShowPlayer::OnBnClickedResume()
{
    if (pMediaControl) pMediaControl->Run();
}

void CDirectShowPlayer::OnBnClickedStop()
{
    if (pMediaControl) { pMediaControl->Stop(); CleanUp(); }
}

void CDirectShowPlayer::OnBnClickedClose()
{
    CleanUp();
    CDialogEx::OnClose();
    KillTimer(1);
    EndDialog(IDOK);
}

void CDirectShowPlayer::OnTimer(UINT_PTR nIDEvent)
{
    if (pSeek) {
        REFERENCE_TIME rtTotal, rtNow = 0;
        CString s;
        pSeek->GetDuration(&rtTotal);
        pSeek->GetCurrentPosition(&rtNow);
        s.Format(L"Abspielvorgang: %02d:%02d (%d%%)",
            (int)((rtNow / 10000000L) / 60),
            (int)((rtNow / 10000000L) % 60),
            (int)((rtNow * 100) / rtTotal));
        GetDlgItem(IDC_STATUS)->SetWindowText(s);
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos((int)(rtNow / 1000000));
    }
    else {
        GetDlgItem(IDC_STATUS)->SetWindowText(L"Abspielvorgang: 00:00 (0%)");
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos(0);
    }
    CDialog::OnTimer(nIDEvent);
}

void CDirectShowPlayer::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* sl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
    if ((pSeek) && ((void*)sl == (void*)pScrollBar)) {
        REFERENCE_TIME pos = (REFERENCE_TIME)sl->GetPos() * 1000000;
        pSeek->SetPositions(&pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    }
    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDirectShowPlayer::OnBnClickedVollbild()
{
    Vollbild(true);
}

void CDirectShowPlayer::Vollbild(bool v)
{
    if (pGraph) {
        IVideoWindow* pVidWin1 = NULL;
        pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin1);
        pVidWin1->put_FullScreenMode(v ? OATRUE : OAFALSE);
        pVidWin1->Release();
    }
}

void CDirectShowPlayer::OnLButtonDown(UINT nFlags, CPoint point)
{
    Vollbild(false);
    CDialogEx::OnLButtonDown(nFlags, point);
}

void CDirectShowPlayer::OnBnClickedSelectfile()
{
    CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, L"Video Files (*.mpg;*.avi;*.mp4)|*.mpg;*.avi;*.mp4|All Files (*.*)|*.*||");
    if (dlg.DoModal() == IDOK) {
        m_FilePath = dlg.GetPathName();
    }
}

void CDirectShowPlayer::OnDropFiles(HDROP hDropInfo)
{
    WCHAR szFileName[MAX_PATH];
    DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
    DragFinish(hDropInfo);
    m_FilePath = szFileName;
}
