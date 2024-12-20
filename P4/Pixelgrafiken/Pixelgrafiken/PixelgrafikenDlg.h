
// PixelgrafikenDlg.h: Headerdatei
//

#pragma once
#include "CDIB.h"
#include "CBlendingDlg.h" // Header für den Blending-Dialog

// CPixelgrafikenDlg-Dialogfeld
class CPixelgrafikenDlg : public CDialogEx
{
// Konstruktion
public:
	CPixelgrafikenDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PIXELGRAFIKEN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	float m_fScale;  // Skalierungsfaktor

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedAufhellen();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedNegativ();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedGraustufen();
	afx_msg void OnBnClickedHistogramm();
	afx_msg void draw_histogramm();
	afx_msg void OnBnClickedKontrast();
	afx_msg void OnBnClickedBlending();
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedGreen();
	afx_msg void OnBnClickedBlue();
	afx_msg void OnBnClickedSharpness();
	afx_msg void OnBnClickedUnsharp();
	afx_msg void OnBnClickedFliph();
	afx_msg void OnBnClickedFlipv();
	afx_msg void OnBnClickedBigger();
	afx_msg void OnBnClickedSmaller();
	afx_msg void OnBnClickedAbdunkeln();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedEmboss();
	afx_msg void OnBnClickedKanten();
	afx_msg void OnBnClickedRelief();
	afx_msg void OnBnClickedLoadjpg();
	afx_msg void OnBnClickedSavejpg();
	afx_msg void OnNMCustomdrawSliderjpg(NMHDR* pNMHDR, LRESULT* pResult);
	CDIB m_dib;
	CDIB m_dibTemp;  // Temporäres Bild für Blending
	CDIB m_dibSave;
};
