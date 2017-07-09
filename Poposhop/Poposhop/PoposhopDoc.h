
// PoposhopDoc.h : CPoposhopDoc 클래스의 인터페이스
//


#pragma once

#include "SamplingDig.h"
#include "QuantizationDlg.h"
#include "Math.h"
#include "ConstantDlg.h"
#include "MaxminDlg.h"
#include "AvgDlg.h"

class CPoposhopDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CPoposhopDoc();
	DECLARE_DYNCREATE(CPoposhopDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
//	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CPoposhopDoc();
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
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	unsigned char *m_InputImage;
	int m_width;
	int m_height;
	int m_size;
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	unsigned char *m_OutputImage;
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;
	void OnDownSampling(void);
	void OnUpSampling(void);
	void OnQuantization(void);
	void OnSumConstant(void);
	void OnSubConstant(void);
	void OnMulConstant(void);
	void OnDivConstant(void);
	void OnNegaTransform(void);
	void OnGammaCorrection(void);
	void OnBinarization(void);
	void OnMaxmin(void);
	void OnAvg(void);
	void OnHistogram(void);
	void OnHistoStretch(void);
	void OnHistoEqual(void);
	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	void OnEmbossing(void);
	double** OnMaskProcess(unsigned char* Target, double Mask[3][3]);
	double** m_tempImage;
	double** Image2DMem(int height, int width);
	double** OnScale(double **Target, int height, int width);
	void OnBlurr(void);
	void OnGaussianFilter(void);
	void OnSharpening(void);
	void OnMedianFilter(void);
	void OnBubleSort(double* mask, int index);
	void OnNearest(void);
	void OnBilinear(void);
	void OnMediansub(void);
	void OnMeansub(void);
	void OnTranslation(void);
	void OnMirrorhor(void);
	void OnRotation(void);
	void OnKuwFilter(void);
};
