#pragma once
#include "resource.h"  // Header für die Ressourcen

class CPixelgrafikenDlg;  // Forward Declaration für den Zeiger auf das Hauptdialogfenster

class CBlendingDlg : public CDialog
{
    DECLARE_DYNAMIC(CBlendingDlg)

public:
    CBlendingDlg(CWnd* pParent = nullptr, CPixelgrafikenDlg* pMainDlg = nullptr); // Konstruktor mit Zeiger auf das Hauptdialogfenster
    virtual ~CBlendingDlg();

    enum { IDD = IDD_BLENDING };
    int GetBlendValue() const { return m_blendValue; }

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV Unterstützung
    DECLARE_MESSAGE_MAP()

private:
    int m_blendValue;
    CSliderCtrl m_blendSlider;
    CPixelgrafikenDlg* m_pDlg;  // Zeiger auf das Hauptdialogfenster (CPixelgrafikenDlg)
    void UpdateLabel(); // Funktion zur Aktualisierung des Textes
public:
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); // Ereignisbehandlung für Slider
};
