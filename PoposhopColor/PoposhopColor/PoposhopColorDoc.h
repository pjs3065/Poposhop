
// PoposhopColorDoc.h : CPoposhopColorDoc Ŭ������ �������̽�
//


#pragma once
#include "kwu.h"

class CPoposhopColorDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CPoposhopColorDoc();
	DECLARE_DYNCREATE(CPoposhopColorDoc)

	// Ư���Դϴ�.
public:

	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// �����Դϴ�.
public:
	virtual ~CPoposhopColorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_width;
	int m_height;
	int m_size;
	int transform;
	int haveColor;
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;
	unsigned char *m_InputImage;
	unsigned char *m_OutputImage;
	unsigned char m_OpenImg[256][256][3];
	unsigned char m_ResultImg[256][256][3];
	unsigned char m_HSI[256][256][3];

	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void OnToHsi(void);
	unsigned char Sol_H(unsigned char R, unsigned char G, unsigned char B);
	unsigned char Sol_S(unsigned char R, unsigned char G, unsigned char B);
	unsigned char Sol_I(unsigned char R, unsigned char G, unsigned char B);
	double Min(double a, double b);
	void OnToRgb(void);
	void OnMenuLightcompensation(void);
	void OnMenuKMeans(void);
	void OnMenuEqualization(void);
	void OnMenuKuwahara(void);

	double** Image2DMem(int height, int width);


	double getAvg(double mask[], int length);
	double getVariance(double mask[], int length);
	double* OnDivideMask(double g[], int length, int start);
	bool isValid(int x, int y, int width, int hegiht);
	kwu getMin(kwu A, kwu B, kwu C, kwu D);
	void init(kwu A, kwu B, kwu C, kwu D);
};


