#pragma once

class CDIB {
public:
	CDIB();
	~CDIB();
	virtual bool Load(CString fname);     // Load from file  
	virtual bool Save(CString fname);		// Save to file virtual 
	void Draw(CDC* pDC, int x, int y);
	virtual int DibWidth();
	virtual int DibHeight();

	void* CDIB::GetPixelAddress(int x, int y);
	int CDIB::StorageWidth();

	void CDIB::brighten(int value);
	void CDIB::negative();
	void CDIB::grey();
	void CDIB::histogramm(float* h, float zoom = 0.1f);
	void CDIB::contrast(float alpha);
	void CDIB::blending(CDIB& b1, CDIB& b2, int p);
	void CDIB::rgb(char ch);
	void CDIB::matrix(int* matrix, int matrixsize, int koeff, char offset = 0);
	void CDIB::flip(char c);

protected:
	BITMAPFILEHEADER* m_pBMFH;		// Pointer to BITMAPFILEHEADER 
	BITMAPINFO* m_pBMI;				// Pointer to BITMAPINFO struct
	BYTE* m_pBits;						// Pointer to Pixelbits
	DWORD m_dwLength;					// length of DIB (including headers)
};