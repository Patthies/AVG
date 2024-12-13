#include "pch.h"
#include "framework.h"
#include "DirectShowPlayer.h"
#include "DirectShowPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static UINT NEAR WM_GRAPHNOTIFY = RegisterWindowMessage(L"GRAPHNOTIFY");


// CDirectShowPlayerDlg-Dialogfeld

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
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_PLAY, &CDirectShowPlayerDlg::OnBnClickedPlay)
    ON_BN_CLICKED(IDC_STOP, &CDirectShowPlayerDlg::OnBnClickedStop)
    ON_BN_CLICKED(IDC_PAUSE, &CDirectShowPlayerDlg::OnBnClickedPause)
    ON_BN_CLICKED(IDC_RESUME, &CDirectShowPlayerDlg::OnBnClickedResume)
    ON_REGISTERED_MESSAGE(WM_GRAPHNOTIFY, GetIt)
    ON_BN_CLICKED(IDC_CLOSE, &CDirectShowPlayerDlg::OnBnClickedClose)
    ON_WM_TIMER()
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_FULLSCREEN, &CDirectShowPlayerDlg::OnBnClickedFullscreen)
    ON_WM_LBUTTONDOWN()
    ON_BN_CLICKED(IDC_OPEN, &CDirectShowPlayerDlg::OnBnClickedOpen)
    ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDirectShowPlayerDlg-Meldungshandler

BOOL CDirectShowPlayerDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Hinzufügen des Menübefehls "Info..." zum Systemmenü.

    // Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
    //  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
    SetIcon(m_hIcon, TRUE);      // Großes Symbol verwenden
    SetIcon(m_hIcon, FALSE);    // Kleines Symbol verwenden

    // TODO: Hier zusätzliche Initialisierung einfügen
    DragAcceptFiles(TRUE);

    //CoInitialize(NULL); // zur Initialisierung des COM-Interfaces
    HRESULT hr = m_DirectShowPlayer.Initialize();
    if (FAILED(hr))
    {
        AfxMessageBox(L"Failed to initialize DirectShow");
        return FALSE;
    }
    SetTimer(1, 200, 0);

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
    HRESULT hr = m_DirectShowPlayer.LoadFile(pSelectedFilePath);
    if (FAILED(hr))
    {
        AfxMessageBox(L"Failed to load media file");
        return;
    }

    m_DirectShowPlayer.ConfigureVideoWindow(this->GetSafeHwnd(), WM_GRAPHNOTIFY);
    m_DirectShowPlayer.SetVideoWindowPosition(10, 10, 500, 300);
    m_DirectShowPlayer.Play();

    // Set up the slider control
    REFERENCE_TIME duration = 0;
    if (SUCCEEDED(m_DirectShowPlayer.GetDuration(&duration)))
    {
        CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
        pSlider->SetRange(0, (int)(duration / 1000000));
        pSlider->SetPos(0);
    }
}

LRESULT CDirectShowPlayerDlg::GetIt(WPARAM wparam, LPARAM lparam) {
    m_DirectShowPlayer.HandleGraphEvent();
    return 0;
}

void CDirectShowPlayerDlg::CleanUp() {
    m_DirectShowPlayer.CleanUp();
}


void CDirectShowPlayerDlg::OnBnClickedStop()
{
    m_DirectShowPlayer.Stop();
}


void CDirectShowPlayerDlg::OnBnClickedPause()
{
    m_DirectShowPlayer.Pause();
}


void CDirectShowPlayerDlg::OnBnClickedResume()
{
    m_DirectShowPlayer.Play();
}


void CDirectShowPlayerDlg::OnBnClickedClose()
{
    m_DirectShowPlayer.CleanUp();
    CDialogEx::OnClose();
    // Timer stoppen
    KillTimer(1);
    // Dialog schließen durch Beenden
    EndDialog(IDOK);
}


void CDirectShowPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
    REFERENCE_TIME rtTotal = 0, rtNow = 0;
    CString s;

    if (SUCCEEDED(m_DirectShowPlayer.GetDuration(&rtTotal)) &&
        SUCCEEDED(m_DirectShowPlayer.GetCurrentPosition(&rtNow)))
    {
        s.Format(L"Playback: %02d:%02d (%d%%)",
            (int)((rtNow / 10000000L) / 60),
            (int)((rtNow / 10000000L) % 60),
            (int)((rtNow * 100) / rtTotal));
        GetDlgItem(IDC_STATUS)->SetWindowText(s);
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos((int)(rtNow / 1000000));
    }
    else
    {
        GetDlgItem(IDC_STATUS)->SetWindowText(L"Playback: 00:00 (0%)");
        ((CSliderCtrl*)GetDlgItem(IDC_SLIDER))->SetPos(0);
    }

    CDialogEx::OnTimer(nIDEvent);
}


void CDirectShowPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
    if ((void*)pSlider == (void*)pScrollBar)
    {
        REFERENCE_TIME pos = (REFERENCE_TIME)pSlider->GetPos() * 1000000;
        m_DirectShowPlayer.SeekToPosition(pos);
    }
    CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDirectShowPlayerDlg::OnBnClickedFullscreen()
{
    m_DirectShowPlayer.SetFullScreenMode(true);
}


void CDirectShowPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_DirectShowPlayer.SetFullScreenMode(false);
    CDialogEx::OnLButtonDown(nFlags, point);
}


void CDirectShowPlayerDlg::OnBnClickedOpen()
{
    // Instantiate CFileDialog for opening a file as a local object
    CFileDialog fileDlg(
        TRUE, // TRUE for Open dialog, FALSE for Save As
        NULL, // Default extension
        NULL, // Default file name
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // Flags
        _T("Video Files (*.avi;*.mp4;*.mkv;*.mov;*.wmv;*.flv;*.mpg)|*.avi;*.mp4;*.mkv;*.mov;*.wmv;*.flv;*.mpg|All Files (*.*)|*.*||"),
        this // Parent window
    );

    fileDlg.m_ofn.lpstrTitle = _T("Select a File to Open");

    if (fileDlg.DoModal() == IDOK)
    {
        pSelectedFilePath = fileDlg.GetPathName();
        SetWindowTextW(pSelectedFilePath);
    }
}


void CDirectShowPlayerDlg::OnDropFiles(HDROP hDropInfo)
{
    UINT nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0); // Get the number of files dropped

    if (nFiles > 0)
    {
        for (UINT i = 0; i < nFiles; ++i)
        {
            TCHAR szFilePath[MAX_PATH] = { 0 };
            if (DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH))
            {
                CString droppedFilePath(szFilePath);

                if (IsSupportedVideoFile(droppedFilePath))
                {
                    pSelectedFilePath = droppedFilePath;
                    SetWindowTextW(pSelectedFilePath);
                }
                else
                {
                    AfxMessageBox(_T("Unsupported file type: ") + droppedFilePath);
                }
            }
        }
    }
    else
    {
        AfxMessageBox(_T("No files were dropped."));
    }

    DragFinish(hDropInfo);
    CDialogEx::OnDropFiles(hDropInfo);
}

bool CDirectShowPlayerDlg::IsSupportedVideoFile(const CString& filePath)
{
    CString extension = filePath.Right(filePath.GetLength() - filePath.ReverseFind('.') - 1).MakeLower();

    const CString supportedExtensions[] = { _T("avi"), _T("mp4"), _T("mkv"), _T("mov"), _T("wmv"), _T("flv"), _T("mpg"), _T("mpeg"), _T("3gp"), _T("webm") };

    for (const CString& ext : supportedExtensions)
    {
        if (extension == ext)
            return true;
    }

    return false;
}