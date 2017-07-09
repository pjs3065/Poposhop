
// PoposhopColorView.h : CPoposhopColorView Ŭ������ �������̽�
//

#pragma once


class CPoposhopColorView : public CView
{
protected: // serialization������ ��������ϴ�.
	CPoposhopColorView();
	DECLARE_DYNCREATE(CPoposhopColorView)

// Ư���Դϴ�.
public:
	CPoposhopColorDoc* GetDocument() const;

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
	virtual ~CPoposhopColorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnToHsi();
	afx_msg void OnToRgb();
	afx_msg void OnMenuLightcompensation();
	afx_msg void OnMenuKMeans();
	afx_msg void OnMenuEqualization();
	afx_msg void OnMenuKuwahara();
};

#ifndef _DEBUG  // PoposhopColorView.cpp�� ����� ����
inline CPoposhopColorDoc* CPoposhopColorView::GetDocument() const
   { return reinterpret_cast<CPoposhopColorDoc*>(m_pDocument); }
#endif

