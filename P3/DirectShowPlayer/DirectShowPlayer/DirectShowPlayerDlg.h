#pragma once
#include "DirectShowMain.h"

// CMFCDiretShowDlg-Dialogfeld
class CDirectShowPlayerDlg : public CDialogEx
{
public:
    CDirectShowPlayerDlg(CWnd* pParent = nullptr);    // Standardkonstruktor

    // Dialogfelddaten
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DSHOWPLAYER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    // Implementierung
protected:
    HICON m_hIcon;
    DirectShowMain m_DirectShowPlayer;
    CString pSelectedFilePath;

    // Generierte Funktionen für die Nachrichtentabellen
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnBnClickedPlay();
    afx_msg void OnBnClickedStop();
    afx_msg void OnBnClickedPause();
    afx_msg void OnBnClickedResume();
    afx_msg void OnBnClickedClose();
    afx_msg void OnBnClickedFullscreen();
    afx_msg void OnBnClickedOpen();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnDropFiles(HDROP hDropInfo);
    afx_msg LRESULT GetIt(WPARAM wparam, LPARAM lparam);

    void CleanUp();
    bool IsSupportedVideoFile(const CString& filePath);

    DECLARE_MESSAGE_MAP()
};