// DSoundDlg.cpp: Implementierungsdatei
// 

#include "pch.h"
#include "framework.h"
#include "DSound.h"
#include "DSoundDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDSoundDlg-Dialogfeld


CDSoundDlg::CDSoundDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DSOUND_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSoundDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDSoundDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Stop, &CDSoundDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_264Hz, &CDSoundDlg::OnBnClicked264hz)
	ON_BN_CLICKED(IDC_CTonleiter, &CDSoundDlg::OnBnClickedCtonleiter)
	ON_BN_CLICKED(IDC_PCMSound, &CDSoundDlg::OnBnClickedPcmsound)
	ON_BN_CLICKED(IDC_CDreiklang, &CDSoundDlg::OnBnClickedCdreiklang)
	ON_BN_CLICKED(IDC_CKlavier, &CDSoundDlg::OnBnClickedCklavier)
	ON_BN_CLICKED(IDC_DKlavier, &CDSoundDlg::OnBnClickedDklavier)
	ON_BN_CLICKED(IDC_EKlavier, &CDSoundDlg::OnBnClickedEklavier)
	ON_BN_CLICKED(IDC_FKlavier, &CDSoundDlg::OnBnClickedFklavier)
	ON_BN_CLICKED(IDC_GKlavier, &CDSoundDlg::OnBnClickedGklavier)
	ON_BN_CLICKED(IDC_AKlavier, &CDSoundDlg::OnBnClickedAklavier)
	ON_BN_CLICKED(IDC_HKlavier, &CDSoundDlg::OnBnClickedHklavier)
	ON_BN_CLICKED(IDC_C2Klavier, &CDSoundDlg::OnBnClickedC2klavier)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_Balance, &CDSoundDlg::OnNMCustomdrawBalance)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_Lautstaerke, &CDSoundDlg::OnNMCustomdrawLautstaerke)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDSoundDlg-Meldungshandler

BOOL CDSoundDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	if (!m_ds.Create(this)) 
		OnCancel();
 
	// create a 4 second sound buffer 
	if ((lpDSBSecondary = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondaryDreiklang = m_ds.CreateSoundBuffer(2, 16, 22050, 3)) == 0)
		OnCancel();
	if ((lpDSBSecondaryTonleiter = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondaryC = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryD = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryE = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryF = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryG = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryA = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryH = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryC2 = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();

	// den Ton c für 2 Sekunden generieren, zyklisch
	m_ds.GenerateSound(lpDSBSecondary,0,2,264);

	// C-Dur Tonleiter einzelne Töne
	int d = 264; //Hz
	m_ds.GenerateSound(lpDSBSecondaryC, 0, 2, d);
	m_ds.GenerateSound(lpDSBSecondaryD, 0, 2, d * 9 / 8.);
	m_ds.GenerateSound(lpDSBSecondaryE, 0, 2, d * 5 / 4.);
	m_ds.GenerateSound(lpDSBSecondaryF, 0, 2, d * 4 / 3.);
	m_ds.GenerateSound(lpDSBSecondaryG, 0, 2, d * 3 / 2.);
	m_ds.GenerateSound(lpDSBSecondaryA, 0, 2, d * 5 / 3.);
	m_ds.GenerateSound(lpDSBSecondaryH, 0, 2, d * 15 / 8.);
	m_ds.GenerateSound(lpDSBSecondaryC2, 0, 2, d * 2);

	// C-Dur Dreiklang 
	// TODO: rausfinden ob hier gemeint ist dass die Töne gleichzeitig abgespielt werden oder ob es so richtig ist wie ich es gemacht habe
	m_ds.GenerateSound(lpDSBSecondaryDreiklang, 0, 1, 264);
	m_ds.GenerateSound(lpDSBSecondaryDreiklang, 1, 1, 330);
	m_ds.GenerateSound(lpDSBSecondaryDreiklang, 2, 1, 396);

	// C-Dur Tonleiter Doppelpuffertechnik
	ton[0]= d; 
	ton[1]= d*9/8.; 
	ton[2]= d*5/4.; 
	ton[3]= d*4/3.; 
	ton[4]= d*3/2.; 
	ton[5]= d*5/3.; 
	ton[6]= d*15/8.; 
	ton[7]= d*2; 
	ton[8]= 0;
	m_ds.GenerateSound(lpDSBSecondaryTonleiter, 0, 2, d);

	// Hole den Balance-Slider und setze ihn auf die Mittelposition (50)
	CSliderCtrl* pBalanceSlider = (CSliderCtrl*)GetDlgItem(IDC_Balance);
	pBalanceSlider->SetRange(0, 100);  // Slider-Bereich
	pBalanceSlider->SetPos(50);        // Mittelposition als Standard

	// Setze den Anfangswert für die Balance auf 0 Dezibel (zentriert)
	int balanceValue = 50;               // Mittelwert des Sliders
	LONG balanceDb = (balanceValue - 50) * 200;

	// Balance-Wert auf alle Soundbuffer anwenden
	m_ds.SetBalance(lpDSBSecondary, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryTonleiter, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryDreiklang, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryC, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryD, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryE, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryF, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryG, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryA, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryH, balanceDb);
	m_ds.SetBalance(lpDSBSecondaryC2, balanceDb);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CDSoundDlg::OnPaint()
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
// das minimierte Fenster mit der Maus zieht.
HCURSOR CDSoundDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDSoundDlg::OnBnClickedStop()
{
	m_ds.Stop(lpDSBSecondary);
	m_ds.Stop(lpDSBSecondaryDreiklang);
	m_ds.Stop(lpDSBSecondaryTonleiter);
	m_ds.Stop(lpDSBSecondaryC);
	m_ds.Stop(lpDSBSecondaryD);
	m_ds.Stop(lpDSBSecondaryE);
	m_ds.Stop(lpDSBSecondaryF);
	m_ds.Stop(lpDSBSecondaryG);
	m_ds.Stop(lpDSBSecondaryA);
	m_ds.Stop(lpDSBSecondaryH);
	m_ds.Stop(lpDSBSecondaryC2);
}

void CDSoundDlg::OnBnClicked264hz()
{
	if (!m_ds.Play(lpDSBSecondary, true)) 
		OnCancel();
}

void CDSoundDlg::OnBnClickedCtonleiter()
{
	if (!m_ds.Play(lpDSBSecondaryTonleiter, true))
		OnCancel();
	SetTimer(1, 700, 0);
}

void CDSoundDlg::OnBnClickedPcmsound()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
}

void CDSoundDlg::OnBnClickedCdreiklang()
{
	if (!m_ds.Play(lpDSBSecondaryDreiklang, true))
		OnCancel();
}

void CDSoundDlg::OnBnClickedCklavier()
{
	if (!m_ds.Play(lpDSBSecondaryC, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedDklavier()
{
	if (!m_ds.Play(lpDSBSecondaryD, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedEklavier()
{
	if (!m_ds.Play(lpDSBSecondaryE, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedFklavier()
{
	if (!m_ds.Play(lpDSBSecondaryF, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedGklavier()
{
	if (!m_ds.Play(lpDSBSecondaryG, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedAklavier()
{
	if (!m_ds.Play(lpDSBSecondaryA, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedHklavier()
{
	if (!m_ds.Play(lpDSBSecondaryH, false))
		OnCancel();
}

void CDSoundDlg::OnBnClickedC2klavier()
{
	if (!m_ds.Play(lpDSBSecondaryC2, false))
		OnCancel();
}

void CDSoundDlg::OnNMCustomdrawBalance(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	// Hole die aktuelle Position des Balance-Schiebereglers
	CSliderCtrl* pBalanceSlider = (CSliderCtrl*)GetDlgItem(IDC_Balance);
	int balanceValue = pBalanceSlider->GetPos();

	// Konvertiere in Dezibelbereich von -10.000 (voll links) bis +10.000 (voll rechts)
	LONG balanceDb = (balanceValue - 50) * 200;

	// Setze Balance
	if (!m_ds.SetBalance(lpDSBSecondary, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryTonleiter, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryDreiklang, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryC, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryD, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryE, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryF, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryG, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryA, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryH, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryC2, balanceDb))
		OnCancel();
}

void CDSoundDlg::OnNMCustomdrawLautstaerke(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	// Hole die aktuelle Position des Lautstärke-Schiebereglers
	CSliderCtrl* pVolumeSlider = (CSliderCtrl*)GetDlgItem(IDC_Lautstaerke);
	int volumeValue = pVolumeSlider->GetPos();

	// Konvertiere in Dezibelbereich von 0 (laut) bis -1000 (stumm)
	LONG volumeDb = -volumeValue * 10;

	// Setze Lautstärke
	if (!m_ds.SetPlaybackVolume(lpDSBSecondary, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryTonleiter, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryDreiklang, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryC, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryD, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryE, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryF, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryG, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryA, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryH, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryC2, volumeDb))
		OnCancel();
}

void CDSoundDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int j=0, buffnr=1, playpos; 
	if ((playpos=m_ds.GetPlayPosition(lpDSBSecondaryTonleiter))==-1) { 
		KillTimer(1); return; 
	} 
	if (((playpos > 50) && (buffnr==0)) || ((playpos < 50) && (buffnr==1))) { 
		if ((++j)==9) {
			KillTimer(1); 
			j=0; 
			if (!m_ds.Stop(lpDSBSecondaryTonleiter)) 
				return; 
			return; 
		} 
		m_ds.GenerateSound(lpDSBSecondaryTonleiter,buffnr*2,2, ton[j]); 
		if (buffnr==1) buffnr=0;
		else buffnr=1; 
	} 

	CDialogEx::OnTimer(nIDEvent);
}
