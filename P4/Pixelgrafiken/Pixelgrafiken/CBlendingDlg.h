#pragma once

class CBlendingDlg : public CDialog
{
    DECLARE_DYNAMIC(CBlendingDlg)

public:
    CBlendingDlg(CWnd* pParent = nullptr);
    virtual ~CBlendingDlg();

    enum { IDD = IDD_BLENDING };
    int GetBlendValue() const { return m_blendValue; }

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    DECLARE_MESSAGE_MAP()


private:
    int m_blendValue;
    CSliderCtrl m_blendSlider;
    void UpdateLabel();
public:
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};