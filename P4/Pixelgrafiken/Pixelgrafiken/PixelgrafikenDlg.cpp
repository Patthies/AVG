
// PixelgrafikenDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "Pixelgrafiken.h"
#include "PixelgrafikenDlg.h"
#include "afxdialogex.h"
#include "CDIB.h"
#include "CBlendingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPixelgrafikenDlg-Dialogfeld


CPixelgrafikenDlg::CPixelgrafikenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PIXELGRAFIKEN_DIALOG, pParent)
	, m_fScale(1.0f)  // Standardskalierung = 100%
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPixelgrafikenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelgrafikenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_AUFHELLEN, &CPixelgrafikenDlg::OnBnClickedAufhellen)
	ON_BN_CLICKED(IDC_LOAD, &CPixelgrafikenDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_NEGATIV, &CPixelgrafikenDlg::OnBnClickedNegativ)
	ON_BN_CLICKED(IDC_SAVE, &CPixelgrafikenDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_GRAUSTUFEN, &CPixelgrafikenDlg::OnBnClickedGraustufen)
	ON_BN_CLICKED(IDC_HISTOGRAMM, &CPixelgrafikenDlg::OnBnClickedHistogramm)
	ON_BN_CLICKED(IDC_KONTRAST, &CPixelgrafikenDlg::OnBnClickedKontrast)
	ON_BN_CLICKED(IDC_BLENDING, &CPixelgrafikenDlg::OnBnClickedBlending)
	ON_BN_CLICKED(IDC_RED, &CPixelgrafikenDlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_GREEN, &CPixelgrafikenDlg::OnBnClickedGreen)
	ON_BN_CLICKED(IDC_BLUE, &CPixelgrafikenDlg::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_SHARPNESS, &CPixelgrafikenDlg::OnBnClickedSharpness)
	ON_BN_CLICKED(IDC_UNSHARP, &CPixelgrafikenDlg::OnBnClickedUnsharp)
	ON_BN_CLICKED(IDC_FLIPH, &CPixelgrafikenDlg::OnBnClickedFliph)
	ON_BN_CLICKED(IDC_FLIPV, &CPixelgrafikenDlg::OnBnClickedFlipv)
	ON_BN_CLICKED(IDC_BIGGER, &CPixelgrafikenDlg::OnBnClickedBigger)
	ON_BN_CLICKED(IDC_SMALLER, &CPixelgrafikenDlg::OnBnClickedSmaller)
	ON_BN_CLICKED(IDC_ABDUNKELN, &CPixelgrafikenDlg::OnBnClickedAbdunkeln)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_EMBOSS, &CPixelgrafikenDlg::OnBnClickedEmboss)
	ON_BN_CLICKED(IDC_KANTEN, &CPixelgrafikenDlg::OnBnClickedKanten)
	ON_BN_CLICKED(IDC_RELIEF, &CPixelgrafikenDlg::OnBnClickedRelief)
	ON_BN_CLICKED(IDC_LOADJPG, &CPixelgrafikenDlg::OnBnClickedLoadjpg)
	ON_BN_CLICKED(IDC_SAVEJPG, &CPixelgrafikenDlg::OnBnClickedSavejpg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDERJPG, &CPixelgrafikenDlg::OnNMCustomdrawSliderjpg)
END_MESSAGE_MAP()


// CPixelgrafikenDlg-Meldungshandler

BOOL CPixelgrafikenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDERJPG);
	if (pSlider)
	{
		pSlider->SetRange(0, 100);
		pSlider->SetPos(90); // Standardwert auf 90 setzen
	}

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}


// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.


void CPixelgrafikenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);

		if (m_dib.DibWidth() > 0 && m_dib.DibHeight() > 0)
		{
			CRect clientRect;
			GetClientRect(&clientRect);

			// Berechne die skalierten Dimensionen
			int scaledWidth = static_cast<int>(m_dib.DibWidth() * m_fScale);
			int scaledHeight = static_cast<int>(m_dib.DibHeight() * m_fScale);

			// Setze die Startposition auf (0, 0)
			int x = 0;
			int y = 0;

			// Definiere das Rechteck für das skalierte Bild
			CRect drawRect(x, y, x + scaledWidth, y + scaledHeight);

			// Zeichne das Bild an den neuen Koordinaten
			m_dib.DrawRect(&dc, drawRect);
		}
		else
		{
			CDialogEx::OnPaint();
		}
	}
}



// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CPixelgrafikenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPixelgrafikenDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein, und/oder benutzen Sie den Standard.
	//CClientDC dc(this);
	//BYTE* p = (BYTE*)m_dib.GetPixelAddress(point.x, point.y);
	//if (p) {
	//	p[0] = p[1] = p[2] = 0;
	//	m_dib.Draw(&dc, 0, 0);
	//	m_dib.Save(L"testsave.bmp");
	//}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CPixelgrafikenDlg::OnBnClickedLoad()
{
	m_dib.Load(L"bild.bmp");		// bmp Bild öffnen
	RedrawWindow();					// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedLoadjpg()
{
	m_dib.LoadJpeg(L"bild.jpg");	// jpg Bild öffnen
	RedrawWindow();					// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedSave()
{
	m_dib.Save(L"save.bmp");
}


void CPixelgrafikenDlg::OnBnClickedSavejpg()
{
	// Sliderwert abrufen
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDERJPG);
	int compressionValue = 90; // Fallback, falls Slider nicht gefunden wird
	if (pSlider)
	{
		compressionValue = pSlider->GetPos();
	}

	m_dib.SaveJpeg(L"bild.jpg", compressionValue);
}


void CPixelgrafikenDlg::OnNMCustomdrawSliderjpg(NMHDR* pNMHDR, LRESULT* pResult)
{
	// Slider-Control abrufen
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDERJPG);
	if (pSlider)
	{
		// Slider-Wert holen
		int sliderValue = pSlider->GetPos();

		// Static Text-Control abrufen
		CStatic* pStaticText = (CStatic*)GetDlgItem(IDC_SLIDERVALUE);
		if (pStaticText)
		{
			// Slider-Wert in einen CString konvertieren
			CString strValue;
			strValue.Format(L"%d", sliderValue);

			// Static Text aktualisieren
			pStaticText->SetWindowTextW(strValue);
		}
	}

	*pResult = 0;
}


void CPixelgrafikenDlg::OnBnClickedAufhellen()
{
	m_dib.brighten(10); // Aufhellen um 10 Prozent 
	RedrawWindow();     // sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedAbdunkeln()
{
	m_dib.darken(-10); // Abdunkeln um 10 Prozent 
	RedrawWindow();     // sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedNegativ()
{
	m_dib.negative();	// negativ erstellen
	RedrawWindow();     // sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedGraustufen()
{
	m_dib.grey();		// graustufen erstellen
	RedrawWindow();     // sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedHistogramm()
{
	draw_histogramm();
}


void CPixelgrafikenDlg::draw_histogramm() { 
	float h[256] = { 0.f };
	int x = 10, y = 105;
	CClientDC dc(this);
	m_dib.histogramm(h, 20.f);
	dc.MoveTo(x, y);
	dc.LineTo(x + 255 + 2, y);
	dc.LineTo(x + 255 + 2, y - 101);
	dc.LineTo(x, y - 101);
	dc.LineTo(x, y);
	CPen p(PS_SOLID, 1, RGB(255, 255, 0));
	dc.SelectObject(&p); for (int i = 0; i < 255; i++) {
		dc.MoveTo(x + i + 1, y - 1);
		dc.LineTo(x + i + 1, y - 1 - (100 * h[i]));
	}
}

void CPixelgrafikenDlg::OnBnClickedKontrast()
{
	m_dib.contrast(1.2f);	// Kontrast erhöhen
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedBlending()
{
	if (m_dib.DibWidth() == 0 || m_dib.DibHeight() == 0)
	{
		AfxMessageBox(L"Kein Ausgangsbild geladen!");
		return;
	}

	// Zweites Bild laden
	CFileDialog dlg(TRUE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		L"Image Files (*.bmp;*.jpg;*.jpeg)|*.bmp;*.jpg;*.jpeg|All Files (*.*)|*.*||");

	m_dibSave.Load(L"bild.bmp");
	m_dibSave.flip('v');

	if (dlg.DoModal() == IDOK)
	{
		CString ext = dlg.GetFileExt().MakeLower();
		bool loadSuccess = false;

		// Temporäres Bild laden
		if (ext == L"bmp")
			loadSuccess = m_dibTemp.Load(dlg.GetPathName());
		else if (ext == L"jpg" || ext == L"jpeg")
			loadSuccess = m_dibTemp.LoadJpeg(dlg.GetPathName());

		if (!loadSuccess)
		{
			AfxMessageBox(L"Fehler beim Laden des zweiten Bildes!");
			return;
		}

		// Prüfen ob die Bilder die gleiche Größe haben
		if (m_dibSave.DibWidth() != m_dibTemp.DibWidth() ||
			m_dibSave.DibHeight() != m_dibTemp.DibHeight())
		{
			AfxMessageBox(L"Die Bilder müssen die gleiche Größe haben!");
			return;
		}

		// Blending-Dialog anzeigen und den Zeiger auf das Hauptdialogfenster übergeben
		CBlendingDlg dlgBlend(this, this);
		if (dlgBlend.DoModal() == IDOK)
		{
			// Blending auf das Bild anwenden und das Bild neu zeichnen
			m_dib.blending(m_dibSave, m_dibTemp, dlgBlend.GetBlendValue());
			Invalidate();  // Bild neu zeichnen
		}
	}
}


void CPixelgrafikenDlg::OnBnClickedRed()
{
	m_dib.rgb('r');			// Rot
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedGreen()
{
	m_dib.rgb('g');			// Grün
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedBlue()
{
	m_dib.rgb('b');			// Blau
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedSharpness()
{ 
	int f = 1; 
	int sharpen_matrix[9] = { -f,-f,-f,-f,9 * f,-f,-f,-f,-f }; 
	m_dib.matrix(sharpen_matrix, 1, f);
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedUnsharp()
{
	int soften_matrix[9] = { 6,12,6,12,25,12,6,12,6 }; 
	m_dib.matrix(soften_matrix, 1, 97);
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedEmboss()
{
	int emboss_matrix[9] = { -1,0,0,0,0,0,0,0,1 }; 
	m_dib.matrix(emboss_matrix, 1, 1, 127);
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedKanten()
{
	int edge_matrix[9] = { -1,-1,-1,-1,8,-1,-1,-1,-1 }; 
	m_dib.matrix(edge_matrix, 1, 1);
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedRelief()
{
	int relief_matrix[9] = { -2,-1,0,-1,1,1,0,1,2 }; 
	m_dib.matrix(relief_matrix, 1, 1);
	RedrawWindow();			// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedFliph()
{
	m_dib.flip('h');	// flip horizontal
	RedrawWindow();		// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedFlipv()
{
	m_dib.flip('v');	// flip vertikal
	RedrawWindow();		// sende WM_PAINT-Ereignis
}


void CPixelgrafikenDlg::OnBnClickedBigger()
{
	m_fScale *= 1.2f;  // Vergrößere um 20%
	Invalidate();
}


void CPixelgrafikenDlg::OnBnClickedSmaller()
{
	m_fScale *= 0.8f;  // Verkleinere um 20%

	// Verhindere zu starkes Verkleinern
	if (m_fScale < 0.1f)
		m_fScale = 0.1f;

	Invalidate();
}


void CPixelgrafikenDlg::OnLButtonDown(UINT nFlags, CPoint point)
{	
	OnBnClickedLoad();

	CDialogEx::OnLButtonDown(nFlags, point);
}