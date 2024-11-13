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
	ON_BN_CLICKED(IDC_CHECKGuitar, &CDSoundDlg::OnBnClickedCheckguitar)
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
 
	// create a sound buffer 
	if ((lpDSBSecondary = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondaryGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 4)) == 0)
		OnCancel();

	if ((lpDSBSecondaryTonleiter = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();
	if ((lpDSBSecondaryTonleiterGuitar = m_ds.CreateSoundBuffer(2, 16, 22050, 16)) == 0)
		OnCancel();

	if ((lpDSBSecondaryC = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryCGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryD = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryDGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryE = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel(); 
	if ((lpDSBSecondaryEGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryF = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryFGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryG = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryGGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryA = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryAGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryH = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryHGuitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryC2 = m_ds.CreateSoundBuffer(2, 16, 22050, 2)) == 0)
		OnCancel();
	if ((lpDSBSecondaryC2Guitar = m_ds.CreateSoundBuffer(2, 16, 44100, 2)) == 0)
		OnCancel();

	if ((lpDSBSecondaryPCM = m_ds.CreateSoundBuffer(2, 16, 22050, 4)) == 0)
		OnCancel();

	// den Ton c für 2 Sekunden generieren, zyklisch
	m_ds.GenerateSound(lpDSBSecondary,0,2,264);

	// den Ton c Guitar für 2 Sekunden generieren, zyklisch
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryGuitar, 0, 1, "C.raw", 0)) OnClose();

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

	// C-Dur Guitar Tonleiter einzelne Töne
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryCGuitar, 0, 1, "C.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryDGuitar, 0, 1, "D.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryEGuitar, 0, 1, "E.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryFGuitar, 0, 1, "F.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryGGuitar, 0, 1, "G.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryAGuitar, 0, 1, "A.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryHGuitar, 0, 1, "H.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryC2Guitar, 0, 1, "C_hoch.raw", 0)) OnClose();

	// C-Dur Tonleiter Doppelpuffertechnik
	int x = 264; //Hz
	ton[0]= x; 
	ton[1]= x * 9 / 8.; 
	ton[2]= x * 5 / 4.; 
	ton[3]= x * 4 / 3.; 
	ton[4]= x * 3 / 2.; 
	ton[5]= x * 5 / 3.; 
	ton[6]= x * 15 / 8.; 
	ton[7]= x * 2; 
	ton[8]= 0;
	m_ds.GenerateSound(lpDSBSecondaryTonleiter, 0, 2, x);

	// C-Dur Tonleiter Guitar
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 0, 2, "C.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 2, 2, "D.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 4, 2, "E.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 6, 2, "F.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 8, 2, "G.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 10, 2, "A.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 12, 2, "H.raw", 0)) OnClose();
	if (!m_ds.GeneratePCMSound(lpDSBSecondaryTonleiterGuitar, 14, 2, "C_hoch.raw", 0)) OnClose();

	// Hole den Balance-Slider und setze ihn auf die Mittelposition (50)
	CSliderCtrl* pBalanceSlider = (CSliderCtrl*)GetDlgItem(IDC_Balance);
	pBalanceSlider->SetRange(0, 100);  // Slider-Bereich
	pBalanceSlider->SetPos(50);        // Mittelposition als Standard

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}


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
	m_ds.Stop(lpDSBSecondaryTonleiter);
	m_ds.Stop(lpDSBSecondaryC);
	m_ds.Stop(lpDSBSecondaryD);
	m_ds.Stop(lpDSBSecondaryE);
	m_ds.Stop(lpDSBSecondaryF);
	m_ds.Stop(lpDSBSecondaryG);
	m_ds.Stop(lpDSBSecondaryA);
	m_ds.Stop(lpDSBSecondaryH);
	m_ds.Stop(lpDSBSecondaryC2);
	m_ds.Stop(lpDSBSecondaryGuitar);
	m_ds.Stop(lpDSBSecondaryTonleiterGuitar);
	m_ds.Stop(lpDSBSecondaryCGuitar);
	m_ds.Stop(lpDSBSecondaryDGuitar);
	m_ds.Stop(lpDSBSecondaryEGuitar);
	m_ds.Stop(lpDSBSecondaryFGuitar);
	m_ds.Stop(lpDSBSecondaryGGuitar);
	m_ds.Stop(lpDSBSecondaryAGuitar);
	m_ds.Stop(lpDSBSecondaryHGuitar);
	m_ds.Stop(lpDSBSecondaryC2Guitar);
	m_ds.Stop(lpDSBSecondaryPCM);
}

void CDSoundDlg::OnBnClicked264hz()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryGuitar, true))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondary, true))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedCtonleiter()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryTonleiterGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryTonleiter, true))
			OnCancel();
		SetTimer(1, 700, 0);
	}
}

void CDSoundDlg::OnBnClickedPcmsound()
{
	if (!m_ds.Play(lpDSBSecondaryPCM, true))
		OnCancel();
	m_ds.GeneratePCMSound(lpDSBSecondaryPCM, 0, 2, "sound.pcm", 0);

	SetTimer(2, 700, NULL);
}

void CDSoundDlg::OnBnClickedCdreiklang()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryCGuitar, false))
			OnCancel();
		if (!m_ds.Play(lpDSBSecondaryEGuitar, false))
			OnCancel();
		if (!m_ds.Play(lpDSBSecondaryGGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryC, false))
			OnCancel();
		if (!m_ds.Play(lpDSBSecondaryE, false))
			OnCancel();
		if (!m_ds.Play(lpDSBSecondaryG, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedCklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryCGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryC, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedDklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryDGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryD, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedEklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryEGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryE, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedFklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryFGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryF, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedGklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryGGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryG, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedAklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryAGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryA, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedHklavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryHGuitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryH, false))
			OnCancel();
	}
}

void CDSoundDlg::OnBnClickedC2klavier()
{
	if (isGuitarSound) {
		if (!m_ds.Play(lpDSBSecondaryC2Guitar, false))
			OnCancel();
	}
	else {
		if (!m_ds.Play(lpDSBSecondaryC2, false))
			OnCancel();
	}
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
	if (!m_ds.SetBalance(lpDSBSecondaryGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryTonleiterGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryCGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryDGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryEGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryFGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryGGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryAGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryHGuitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryC2Guitar, balanceDb))
		OnCancel();
	if (!m_ds.SetBalance(lpDSBSecondaryPCM, balanceDb))
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
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryTonleiterGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryCGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryDGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryEGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryFGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryGGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryAGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryHGuitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryC2Guitar, volumeDb))
		OnCancel();
	if (!m_ds.SetPlaybackVolume(lpDSBSecondaryPCM, volumeDb))
		OnCancel();

}

void CDSoundDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int j = 0, buffnr = 1, playpos;

	// Timer für C-Dur Tonleiter
	if (nIDEvent == 1) {
		static int j = 0, buffnr = 1, playpos;
		if ((playpos = m_ds.GetPlayPosition(lpDSBSecondaryTonleiter)) == -1) {
			KillTimer(1);
			return;
		}
		if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
			if ((++j) == 9) {
				KillTimer(1);
				j = 0;
				if (!m_ds.Stop(lpDSBSecondaryTonleiter))
					return;
				return;
			}
			m_ds.GenerateSound(lpDSBSecondaryTonleiter, buffnr * 2, 2, ton[j]);
			if (buffnr == 1) buffnr = 0;
			else buffnr = 1;
		}
	}
	if (nIDEvent == 2) {
		if ((playpos = m_ds.GetPlayPosition(lpDSBSecondaryPCM)) == -1) {
			KillTimer(1); return;
		}
		if (((playpos > 50) && (buffnr == 0)) || ((playpos < 50) && (buffnr == 1))) {
			if ((++j) == 9) { 
				KillTimer(1);
				j = 0;
				if (!m_ds.Stop(lpDSBSecondaryPCM))
					return;
				return;
			}
			m_ds.GeneratePCMSound(lpDSBSecondaryPCM, buffnr * 2, 2, "sound.pcm", j);
			if (buffnr == 1) buffnr = 0; 
			else buffnr = 1;
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDSoundDlg::OnBnClickedCheckguitar()
{
	isGuitarSound = !isGuitarSound;
}
