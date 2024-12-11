#include "pch.h"
#include "CDIB.h"


CDIB::CDIB() {
	m_pBMFH = 0;
	m_pBMI = 0;
	m_pBits = 0;
	m_dwLength = 0L; // init by Zero
}


CDIB::~CDIB() {
	if (m_pBMFH != 0)
		delete[] m_pBMFH; // free the memory.
}


int CDIB::DibWidth() {
	if (m_pBMFH)
		return m_pBMI->bmiHeader.biWidth;
	else return 0;
}


int CDIB::DibHeight() {
	if (m_pBMFH)
		return m_pBMI->bmiHeader.biHeight;
	else return 0;
}


bool CDIB::Load(CString fname) {
	if (m_pBMFH != 0) delete[] m_pBMFH;  // DIB must be empty 
	FILE* fp;
	if ((fp = _wfopen(fname, L"rb")) == NULL) {
		AfxMessageBox(L"Unable to open CDIB-File");
		return false;
	}
	fseek(fp, 0L, SEEK_END);    // Länge der Datei ermitteln 
	m_dwLength = ftell(fp);
	rewind(fp);
	if ((m_pBMFH = (BITMAPFILEHEADER*) new char[m_dwLength]) == 0) {
		AfxMessageBox(L"Unable to allocate DIB-Memory");
		fclose(fp);
		return false;
	}
	if (fread(m_pBMFH, m_dwLength, 1, fp) != 1) {
		AfxMessageBox(L"Read error");
		delete[] m_pBMFH; m_pBMFH = 0;
		fclose(fp);
		return false;
	}
	if (m_pBMFH->bfType != 0x4d42) {
		AfxMessageBox(L"Invalid bitmap file");
		delete[] m_pBMFH; m_pBMFH = 0;
		fclose(fp);
		return false;
	}
	m_pBMI = (BITMAPINFO*)(m_pBMFH + 1);
	m_pBits = (BYTE*)m_pBMFH + m_pBMFH->bfOffBits;
	fclose(fp);
	return true;
}


bool CDIB::Save(CString fname) {
	if (!m_pBMFH)
		return false;
	FILE* fp;
	if ((fp = _wfopen(fname, L"wb")) == NULL) {
		AfxMessageBox(L"Unable to open CDIB-File");
		return false;
	}
	if (fwrite(m_pBMFH, m_dwLength, 1, fp) != 1) {
		AfxMessageBox(L"Write error");
		delete[] m_pBMFH; m_pBMFH = 0;
		fclose(fp);
		return false;
	}
	fclose(fp);
	return true;
}


// Draw the DIB to a given DC 
void CDIB::Draw(CDC* pDC, int x, int y) {
	if (m_pBMFH != 0) {
		pDC->SetStretchBltMode(HALFTONE);
		StretchDIBits(pDC->GetSafeHdc(),
			x,
			y,
			DibWidth(),
			DibHeight(),
			0,
			0,
			DibWidth(),
			DibHeight(),
			m_pBits,
			m_pBMI,
			DIB_RGB_COLORS,
			SRCCOPY);
	}
}


void* CDIB::GetPixelAddress(int x, int y) {
	int iWidth;
	if ((x >= DibWidth()) || (y >= DibHeight())) {
		return NULL;				// pixel is out of range 
	}
	iWidth = StorageWidth();	// Bytes pro Bildzeile 
	if (m_pBMI->bmiHeader.biBitCount == 24)
		return m_pBits + (DibHeight() - y - 1) * iWidth + x * (m_pBMI->bmiHeader.biBitCount / 8);
	return m_pBits + (DibHeight() - y - 1) * iWidth + x;
}


int CDIB::StorageWidth() {
	return (m_pBMI ? ((m_pBMI->bmiHeader.biWidth * (m_pBMI->bmiHeader.biBitCount / 8) + 3) & ~3) : 0);
}


void CDIB::brighten(int value) {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24) || (value < -100) || (value > 100))
		return; // do nothing (not supported) 

	BYTE* t;
	int width = DibWidth() * 3;
	for (int i = 0; i < DibHeight(); i++) {
		t = (BYTE*)GetPixelAddress(0, i);
		for (int j = 0; j < width; j += 3) {
			if (value > 0) { // Aufhellen
				*(t + j) += (BYTE)((255 - *(t + j)) * (value / 100.f));
				*(t + j + 1) += (BYTE)((255 - *(t + j + 1)) * (value / 100.f));
				*(t + j + 2) += (BYTE)((255 - *(t + j + 2)) * (value / 100.f));
			}
			else { // Abdunkeln
				*(t + j) = max(0, *(t + j) + (int)(*(t + j) * (value / 100.f)));
				*(t + j + 1) = max(0, *(t + j + 1) + (int)(*(t + j + 1) * (value / 100.f)));
				*(t + j + 2) = max(0, *(t + j + 2) + (int)(*(t + j + 2) * (value / 100.f)));
			}
		}
	}
}


void CDIB::negative() { 
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24)) 
		return; 
	BYTE* t; 
	int width = DibWidth() * 3; for (int i = 0; i < DibHeight(); i++) { 
		t = (BYTE*)GetPixelAddress(0, i); 
		for (int j = 0; j < width; j += 3) { 
			*(t + j) = 255 - (*(t + j)); 
			*(t + j + 1) = 255 - (*(t + j + 1)); 
			*(t + j + 2) = 255 - (*(t + j + 2)); 
		} 
	} 
}


void CDIB::grey() { 
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24)) 
		return; 
	BYTE* t; 
	int width = DibWidth() * 3; 
	for (int i = 0; i < DibHeight(); i++) { 
		t = (BYTE*)GetPixelAddress(0, i); 
		for (int j = 0; j < width; j += 3) { 
			(*(t + j)) = (*(t + j + 1)) = (*(t + j + 2)) = (BYTE)(0.1145 * (*(t + j)) + 0.5866 * (*(t + j + 1)) + 0.2989 * (*(t + j + 2))); 
		} 
	} 
}


void CDIB::histogramm(float* h, float zoom) {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24)) 
		return; 
	BYTE* t; 
	BYTE g; 
	int width = DibWidth() * 3; 
	float step = 1.f / (DibHeight() * DibWidth()); 
	for (int i = 0; i < 255; i++) h[i] = 0.f; // init 
	
	for (int i=0;i<DibHeight();i++) { 
		t=(BYTE*) GetPixelAddress(0,i); 
		for (int j=0;j<width;j+=3) { 
			g = (BYTE) (0.1145*(*(t+j))+0.5866*(*(t+j+1))+0.2989*(*(t+j+2))); h[g]+=step; // count 
		} 
	} 
	
	if (zoom!=0.0f)     // zoom 
		for (int i=0; i<255; i++) { 
			h[i]*=zoom; 
			if (h[i]>1.f) h[i]=1.f; 
		} 
}


void CDIB::contrast(float alpha) {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24)) 
		return; 
	if (alpha < 0 || alpha>2) { 
		AfxMessageBox(L"Ungültiger Kontrast Alpha-Wert."); 
		return; 
	}

	BYTE* t; 
	int i, j, z; 
	double median = 0.0; 
	unsigned char lut[256]; 
	int width = DibWidth() * 3; //Mittlere Intensität berechnen 
	
	for (i=0;i<DibHeight();i++) { 
		t=(BYTE*) GetPixelAddress(0,i); 
		for (j=0;j<width;j+=3) median+=(int)((0.1145*(*(t+j))+ 0.5866*(*(t+j+1))+0.2989*(*(t+j+2)))); 
	}
	median/=(DibHeight()*DibWidth());
	
	for (i=0;i<256;i++) { 
		z=(int)( (1-alpha)*median + alpha*i ); 
		if (z>255) z=255; 
		else if (z<0) z=0; lut[i]=z;
	} 
	
	for (i=0;i<DibHeight();i++) { 
		t=(BYTE*) GetPixelAddress(0,i); 
		for (j=0;j<width;j+=3) { 
			*(t+j)=lut[*(t+j)]; 
			*(t+j+1)=lut[*(t+j+1)]; 
			*(t+j+2)=lut[*(t+j+2)]; 
		} 
	} 
}


void CDIB::blending(CDIB& b1, CDIB& b2, int p) { 
	if ((m_pBMFH == 0) || (b1.m_pBMFH == 0) || (b2.m_pBMFH == 0)) 
		return; 

	if ((m_pBMI->bmiHeader.biBitCount != 24) || (b1.m_pBMI->bmiHeader.biBitCount != 24) || (b2.m_pBMI->bmiHeader.biBitCount != 24)) 
		return; 

	if ((DibWidth() != b1.DibWidth()) || (DibWidth() != b2.DibWidth()) || (DibHeight() != b1.DibHeight()) || (DibHeight() != b2.DibHeight())) 
		return; 
	
	BYTE* t, * t1, * t2; int width = DibWidth() * 3; 
	for (int i = 0; i < DibHeight(); i++) { 
		t = (BYTE*)GetPixelAddress(0, i); 
		t1 = (BYTE*)b1.GetPixelAddress(0, i); 
		t2 = (BYTE*)b2.GetPixelAddress(0, i); 
		
		for (int j = 0; j < width; j += 3) { 
			*(t + j) = *(t1 + j) + ((*(t2 + j) - *(t1 + j)) * (p / 100.f)); 
			*(t + j + 1) = *(t1 + j + 1) + ((*(t2 + j + 1) - *(t1 + j + 1)) * (p / 100.f)); 
			*(t + j + 2) = *(t1 + j + 2) + ((*(t2 + j + 2) - *(t1 + j + 2)) * (p / 100.f)); 
		} 
	} 
}


void CDIB::rgb(char ch) { 
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24))
		return;
	BYTE* t;
	int width = DibWidth() * 3;
	for (int i = 0; i < DibHeight(); i++) {
		t = (BYTE*)GetPixelAddress(0, i);
		for (int j = 0; j < width; j += 3) {
			switch (ch) {
			case 'r': (*(t + j)) = (*(t + j + 1)) = 0;
				break;
			case 'g': (*(t + j)) = (*(t + j + 2)) = 0;
				break;
			case 'b': (*(t + j + 1)) = (*(t + j + 2)) = 0;
				break;
			}
		}
	}
}


void CDIB::matrix(int* matrix, int matrixsize, int koeff, char offset) {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24)) 
		return; 
	if (koeff == 0) 
		return; 

	BYTE * t, * temp; 
	int sw = StorageWidth(); 
	int red, green, blue, index; 
	int width = DibWidth() * 3; 
	temp = new BYTE[sw * DibHeight()];					// eine temporäre Kopie des Bildes anlegen 
	memcpy(temp, m_pBits, sw*DibHeight()); 
	for (int i=0;i<DibHeight();i++) {					// für alle Zeilen 
		for (int j=0;j<(width-3*matrixsize);j+=3)  {	// und jedes Pixel der Zeile 
			index=0; red=green=blue=offset; 
			for(int k=-matrixsize;k<=matrixsize;k++) { 
				t= temp + ((BYTE*)GetPixelAddress(0,(DibHeight()+i+k)%DibHeight())-m_pBits); 
				for(int l=-3*matrixsize;l<=3*matrixsize;l+=3) { // Matrix abarbeiten 
					blue += (int)(matrix[index] * (*(t+(sw+j+l)  %sw))); 
					green += (int)(matrix[index] * (*(t+(sw+j+1+l)%sw))); 
					red += (int)(matrix[index] * (*(t+(sw+j+2+l)%sw))); 
					index++; 
				} 
			} 
			
			t=(BYTE*) GetPixelAddress(0,i); 
			red/=koeff; green/=koeff; blue/=koeff; 
			(blue<=255)  ? (*(t+j)=(BYTE)blue)    : (*(t+j) = 255); 
			(green<=255) ? (*(t+j+1)=(BYTE)green) : (*(t+j+1) = 255); 
			(red<=255)   ? (*(t+j+2)=(BYTE)red)   : (*(t+j+2) = 255); 
			if (blue<0)  (*(t+j))  =0; 
			if (green<0) (*(t+j+1))=0; 
			if (red<0)   (*(t+j+2))=0; 
		} 
	} 
	delete [] temp; 
}


// "flipping" des Bildes: 'h' - horizontal  'v' - vertikal 
void CDIB::flip(char c) {
	if ((m_pBMFH == 0) || (m_pBMI->bmiHeader.biBitCount != 24))
		return;
	int i;
	switch (c) {
		case 'h': {		// horizontal 
			BYTE* h = new BYTE[StorageWidth()];
			for (i = 0; i < DibHeight() / 2; i++) {
				memcpy(h, GetPixelAddress(0, i), StorageWidth());
				memcpy(GetPixelAddress(0, i), GetPixelAddress(0, DibHeight() - i - 1), StorageWidth());
				memcpy(GetPixelAddress(0, DibHeight() - i - 1), h, StorageWidth());
			}
			delete[] h;
			break;
		}
		case 'v': {		// vertikal 
			BYTE h[3];	// Hilfspixel 
			for (i = 0; i < DibHeight(); i++) {
				for (int j = 0; j < DibWidth() / 2; j++) {
					memcpy(h, GetPixelAddress(j, i), 3);
					memcpy(GetPixelAddress(j, i), GetPixelAddress(DibWidth() - j - 1, i), 3);
					memcpy(GetPixelAddress(DibWidth() - j - 1, i), h, 3);
				}
			}
			break;
		}
	}
}