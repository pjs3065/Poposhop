
// PoposhopView.h : CPoposhopView Ŭ������ �������̽�
//

#pragma once


class CPoposhopView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPoposhopView();
	DECLARE_DYNCREATE(CPoposhopView)

// Ư���Դϴ�.
public:
	CPoposhopDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CPoposhopView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuDownSampling();
	afx_msg void OnMenuUpSampling();
	afx_msg void OnMenuQuantization();
	afx_msg void OnSumConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnMulConstant();
	afx_msg void OnDivConstant();
	afx_msg void OnNegaTransform();
	afx_msg void OnGammaCorrection();
	afx_msg void OnBinarization();
	afx_msg void OnMaxMin();
	afx_msg void OnAvg();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHistogram();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoEqual();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnSharpening();
	afx_msg void OnMedianFilter();
	afx_msg void OnNearestInterpolation();
	afx_msg void OnNearest();
	afx_msg void OnBilinear();
	afx_msg void OnMediansub();
	afx_msg void OnMeansub();
	afx_msg void OnTranslation();
	afx_msg void OnMirrorhor();
	afx_msg void OnRotation();
	afx_msg void OnKuwfilter();
};

#ifndef _DEBUG  // PoposhopView.cpp�� ����� ����
inline CPoposhopDoc* CPoposhopView::GetDocument() const
   { return reinterpret_cast<CPoposhopDoc*>(m_pDocument); }
#endif

