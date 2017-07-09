
// PoposhopColorDoc.h : CPoposhopColorDoc 클래스의 인터페이스
//


#pragma once
#include "kwu.h"

class CPoposhopColorDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CPoposhopColorDoc();
	DECLARE_DYNCREATE(CPoposhopColorDoc)

	// 특성입니다.
public:

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 구현입니다.
public:
	virtual ~CPoposhopColorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
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


