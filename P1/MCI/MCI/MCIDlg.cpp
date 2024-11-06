
// MCIDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "MCI.h"
#include "MCIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMCIDlg-Dialogfeld



CMCIDlg::CMCIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMCIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMCIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMCIDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMCIDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMCIDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMCIDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMCIDlg::OnBnClickedButton6)
	ON_LBN_SELCHANGE(IDC_LISTBOX, &CMCIDlg::OnLbnSelchangeListbox)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON7, &CMCIDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMCIDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CMCIDlg-Meldungshandler

BOOL CMCIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// TODO: Hier zusätzliche Initialisierung einfügen

	SetTimer(1, 200, 0);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMCIDlg::OnPaint()
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
HCURSOR CMCIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

enum MediaType {
	MEDIA_VIDEO,
	MEDIA_AUDIO_MP3,
	MEDIA_AUDIO_MIDI,
	MEDIA_AUDIO_CD
};

MediaType m_CurrentMediaType;

void CMCIDlg::OnBnClickedButton1()
{
	// Video
	m_CurrentMediaType = MEDIA_VIDEO;

	CRect r;
	GetDlgItem(IDC_DESTIN)->GetWindowRect(r);
	ScreenToClient(r);
	mci.OpenFile(L"video.mpg");
	mci.SetVideoPosition(GetSafeHwnd(),
		CRect(r.left, r.top, r.Width(), r.Height()));

	mci.Play();
}

void CMCIDlg::OnBnClickedButton2()
{
	// Audio mp3
	m_CurrentMediaType = MEDIA_AUDIO_MP3;

	mci.OpenFile(L"audio.mp3");
	mci.Play();
}

void CMCIDlg::OnBnClickedButton3()
{
	// Audio MIDI
	m_CurrentMediaType = MEDIA_AUDIO_MIDI;

	mci.OpenFile(L"audio.mid");
	mci.Play();
}

void CMCIDlg::OnBnClickedButton4()
{
	// Audio CD
	m_CurrentMediaType = MEDIA_AUDIO_CD;

	BYTE tracks;
	mci.OpenAudioCD(0, tracks);

	BYTE min, sek, frame;
	((CListBox*)GetDlgItem(IDC_LISTBOX))->ResetContent();
	RedrawWindow(); // falls vorher ein Video abgespielt wurde
	for (int i = 1; i <= tracks; i++) {
		mci.GetTrackLength(i, min, sek, frame);
		CString temp; // z.B. Eintrag in eine ListBox
		temp.Format(L"[%02d] %02d:%02d", i, min, sek);
		((CListBox*)GetDlgItem(IDC_LISTBOX))->AddString(temp);
	}

	//mci.TMSFSeek(2, 0, 0, 0); // zweiter Titel auf der Audio-CD
	mci.Play();
}

void CMCIDlg::OnBnClickedButton5()
{
	// Play

	mci.Play();
}


void CMCIDlg::OnBnClickedButton6()
{
	// Pause

	mci.Pause();
}

void CMCIDlg::OnBnClickedButton7()
{
	// Exit
	PostMessage(WM_CLOSE);
}

void CMCIDlg::OnBnClickedButton8()
{
	// Close

	mci.Close();
}

void CMCIDlg::OnLbnSelchangeListbox()
{
	// switchen zwischen CD-Tracks

	mci.TMSFSeek(((CListBox*)GetDlgItem(IDC_LISTBOX))->GetCurSel() + 1, 0, 0, 0); 
	mci.Play(); 
}

void CMCIDlg::OnTimer(UINT_PTR nIDEvent)
{
	int pos = 0;
	CString str, str_pct;
	unsigned char t_p, m_p, s_p, f_p;

	// Aktuelle Position abfragen
	mci.GetTMSFPosition(t_p, m_p, s_p, f_p);

	if (m_CurrentMediaType == MEDIA_AUDIO_CD) {
		// Für Audio-CD: Position und Länge des Tracks verwenden
		str.Format(L"[%02d] %02d:%02d", t_p, m_p, s_p);
		SetDlgItemText(IDC_TIME, str);

		// Tracklänge abrufen
		BYTE track_min = 0, track_sec = 0, track_frame = 0;
		if (!mci.GetTrackLength(t_p, track_min, track_sec, track_frame)) {
			track_min = 0;
			track_sec = 1;	// Standardwert, um Division durch Null zu vermeiden
		}

		// Tracklänge in Sekunden berechnen
		int track_length_seconds = track_min * 60 + track_sec;

		// Aktuelle Position in Sekunden berechnen
		pos = m_p * 60 + s_p;

		// Prozentuale Fortschrittsanzeige berechnen
		if (track_length_seconds == 0) {
			track_length_seconds = 1;  // Um Division durch Null zu vermeiden
		}
		str_pct.Format(L"%d %%", (int)(((float)pos / track_length_seconds) * 100));
	}
	else {
		// Für andere Medientypen: Gesamtlänge des Mediums verwenden
		int total_seconds = mci.GetMediaLength(t_p);
		if (total_seconds == 0)
			total_seconds = 1;  // Um Division durch Null zu vermeiden

		// Format für andere Medientypen
		str.Format(L"%02d:%02d", m_p, s_p);
		SetDlgItemText(IDC_TIME, str);

		// Fortschritt berechnen
		pos = (int)s_p;
		str_pct.Format(L"%d %%", (int)(((float)pos / total_seconds) * 100));
	}

	// Anzeige des Fortschritts
	SetDlgItemText(IDC_PROGRESS, str_pct);

	CDialogEx::OnTimer(nIDEvent);
}