#include "pch.h"
#include "PixelgrafikenDlg.h"
#include "Pixelgrafiken.h"
#include "CBlendingDlg.h"
#include "afxdialogex.h"

// CBlendingDlg-Dialog

IMPLEMENT_DYNAMIC(CBlendingDlg, CDialog)

CBlendingDlg::CBlendingDlg(CWnd* pParent, CPixelgrafikenDlg* pMainDlg)
    : CDialog(IDD_BLENDING, pParent), m_pDlg(pMainDlg), m_blendValue(0)  // Startwert auf 50% setzen
{
}

CBlendingDlg::~CBlendingDlg()
{
}

void CBlendingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDERBLENDING, m_blendSlider);  // Slider ansteuern

    if (!pDX->m_bSaveAndValidate)
    {
        m_blendSlider.SetRange(0, 100);  // Setze den Wertebereich des Sliders (0-100%)
        m_blendSlider.SetPos(m_blendValue);  // Setze den Anfangswert des Sliders (0%)
        UpdateLabel();  // Textanzeige für den Slider-Wert aktualisieren
    }
}

BEGIN_MESSAGE_MAP(CBlendingDlg, CDialog)
    ON_WM_HSCROLL() // Ereignis für Slider-Bewegung
END_MESSAGE_MAP()

// Funktion zur Aktualisierung der Textanzeige
void CBlendingDlg::UpdateLabel()
{
    CString str;
    str.Format(L"Überblendung: %d%%", m_blendValue);  // Anzeige des aktuellen Werts
    SetDlgItemText(IDC_BLENDINGVALUE, str);  // Text in der Anzeige setzen
}

// Ereignisbehandlung für die Slider-Bewegung
void CBlendingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    m_blendValue = m_blendSlider.GetPos();  // Den aktuellen Wert des Sliders abfragen
    UpdateLabel();  // Die Textanzeige mit dem neuen Wert aktualisieren

    // Wenn das Hauptdialogfenster (CPixelgrafikenDlg) existiert, das Bild live aktualisieren
    if (m_pDlg)  // Sicherstellen, dass der Zeiger gültig ist
    {
        // Die blending-Funktion im Hauptdialogfenster aufrufen und das Bild mit dem neuen Wert aktualisieren
        m_pDlg->m_dib.blending(m_pDlg->m_dibSave, m_pDlg->m_dibTemp, m_blendValue);
        m_pDlg->RedrawWindow();  // Bild neu zeichnen
    }

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);  // Standardbehandlung des Ereignisses
}