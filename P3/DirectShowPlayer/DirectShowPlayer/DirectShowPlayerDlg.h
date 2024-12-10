
// DirectShowPlayerDlg.h: Headerdatei
//

#pragma once


// CDirectShowPlayerDlg-Dialogfeld
class CDirectShowPlayerDlg : public CDialogEx
{
// Konstruktion
public:
	CDirectShowPlayerDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIRECTSHOWPLAYER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	IGraphBuilder* pGraph;
	IMediaControl* pMediaControl;
	IMediaEventEx* pEvent;
	IVideoWindow* pVidWin = NULL;
	IMediaSeeking* pSeek = NULL;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	void CleanUp();
	void CDirectShowPlayerDlg::Vollbild(bool v);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_FilePath; // Speichert den Dateipfad
	afx_msg void OnDropFiles(HDROP hDropInfo); // Drag-and-Drop-Verarbeitung
	afx_msg void OnBnClickedPlay();
	afx_msg void OnBnClickedPause();
	afx_msg void OnBnClickedResume();
	afx_msg LRESULT GetIt(WPARAM wparam, LPARAM lparam);
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedVollbild();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSelectfile();
};
