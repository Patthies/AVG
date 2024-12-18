// CBlendingDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "PixelgrafikenDlg.h"
#include "Pixelgrafiken.h"
#include "CBlendingDlg.h"
#include "afxdialogex.h"


// CBlendingDlg-Dialog

IMPLEMENT_DYNAMIC(CBlendingDlg, CDialog)

CBlendingDlg::CBlendingDlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_BLENDING, pParent)
    , m_blendValue(50)  // Start bei 50%
{

}

CBlendingDlg::~CBlendingDlg()
{
}

void CBlendingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_SLIDERBLENDING, m_blendSlider);

    if (!pDX->m_bSaveAndValidate)
    {
        m_blendSlider.SetRange(0, 100);  // 0-100%
        m_blendSlider.SetPos(m_blendValue);
        UpdateLabel();
    }
}

BEGIN_MESSAGE_MAP(CBlendingDlg, CDialog)
    ON_WM_HSCROLL()
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


void CBlendingDlg::UpdateLabel()
{
    CString str;
    str.Format(L"Überblendung: %d%%", m_blendValue);
    SetDlgItemText(IDC_BLENDINGVALUE, str);
}

void CBlendingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    m_blendValue = m_blendSlider.GetPos();
    UpdateLabel();

    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
