// DSoundDlg.h: Headerdatei
//

#pragma once
#include "CDirectSound.h"

// CDSoundDlg-Dialogfeld
class CDSoundDlg : public CDialogEx
{
// Konstruktion
public:
	CDSoundDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DSOUND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	CDirectSound m_ds;
	LPDIRECTSOUNDBUFFER 
		lpDSBSecondary, 
		lpDSBSecondaryTonleiter, 
		lpDSBSecondaryC, 
		lpDSBSecondaryD, 
		lpDSBSecondaryE, 
		lpDSBSecondaryF, 
		lpDSBSecondaryG, 
		lpDSBSecondaryA, 
		lpDSBSecondaryH, 
		lpDSBSecondaryC2,
		lpDSBSecondaryGuitar,
		lpDSBSecondaryTonleiterGuitar,
		lpDSBSecondaryCGuitar,
		lpDSBSecondaryDGuitar,
		lpDSBSecondaryEGuitar,
		lpDSBSecondaryFGuitar,
		lpDSBSecondaryGGuitar,
		lpDSBSecondaryAGuitar,
		lpDSBSecondaryHGuitar,
		lpDSBSecondaryC2Guitar,
		lpDSBSecondaryPCM;
	double ton[9];
	bool isGuitarSound;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClicked264hz();
	afx_msg void OnBnClickedCtonleiter();
	afx_msg void OnBnClickedPcmsound();
	afx_msg void OnBnClickedCdreiklang();
	afx_msg void OnBnClickedCklavier();
	afx_msg void OnBnClickedDklavier();
	afx_msg void OnBnClickedEklavier();
	afx_msg void OnBnClickedFklavier();
	afx_msg void OnBnClickedGklavier();
	afx_msg void OnBnClickedAklavier();
	afx_msg void OnBnClickedHklavier();
	afx_msg void OnBnClickedC2klavier();
	afx_msg void OnNMCustomdrawBalance(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawLautstaerke(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCheckguitar();
};
