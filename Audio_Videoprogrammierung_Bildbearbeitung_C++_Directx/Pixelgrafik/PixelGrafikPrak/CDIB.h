#pragma once
class CDIB {
public:
	CDIB();
	~CDIB();
	virtual bool Load(CString fname); // Load from file
	virtual bool Save(CString fname); // Save to file
	virtual void Draw(CDC* pDC, int x, int y);
	virtual int DibWidth();
	virtual int DibHeight();
	
	void* GetPixelAddress(int x, int y);
	int StorageWidth();

	void brighten(int value);
	void darken(int value);
	void negative();

	void grey();
	void histogramm(float *h, float zoom);

	void contrast(float alpha);
	void blending(CDIB& b1, CDIB& b2, int p);
	void rgb(char ch);

	void matrix(int* matrix, int matrixsize, int koeff, char offset);

	void flip(char c);
	bool SaveJpeg(CString FileName, int quality);
	bool LoadJpeg(CString FileName);
			
protected:
	BITMAPFILEHEADER* m_pBMFH; // Pointer to BITMAPFILEHEADER
	BITMAPINFO* m_pBMI; // Pointer to BITMAPINFO struct
	BYTE* m_pBits; // Pointer to Pixelbits
	DWORD m_dwLength; // length of DIB (including headers)
};	

