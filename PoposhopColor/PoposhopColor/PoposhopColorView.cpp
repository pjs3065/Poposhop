
// PoposhopColorView.cpp : CPoposhopColorView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "PoposhopColor.h"
#endif

#include "PoposhopColorDoc.h"
#include "PoposhopColorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoposhopColorView

IMPLEMENT_DYNCREATE(CPoposhopColorView, CView)

	BEGIN_MESSAGE_MAP(CPoposhopColorView, CView)
		// ǥ�� �μ� ����Դϴ�.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_COMMAND(ID_To_HSI, &CPoposhopColorView::OnToHsi)
		ON_COMMAND(ID_To_RGB, &CPoposhopColorView::OnToRgb)
		ON_COMMAND(ID_Menu_LIGHTCOMPENSATION, &CPoposhopColorView::OnMenuLightcompensation)
		ON_COMMAND(ID_Menu_K_Means, &CPoposhopColorView::OnMenuKMeans)
		ON_COMMAND(ID_Menu_Equalization, &CPoposhopColorView::OnMenuEqualization)
		ON_COMMAND(ID_Menu_Kuwahara, &CPoposhopColorView::OnMenuKuwahara)
	END_MESSAGE_MAP()

	// CPoposhopColorView ����/�Ҹ�

	CPoposhopColorView::CPoposhopColorView()
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

	}

	CPoposhopColorView::~CPoposhopColorView()
	{
	}

	BOOL CPoposhopColorView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
		//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

		return CView::PreCreateWindow(cs);
	}

	// CPoposhopColorView �׸���

	void CPoposhopColorView::OnDraw(CDC* pDC)
	{
		CPoposhopColorDoc* pDoc = GetDocument();
		unsigned char R, G, B;

		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		for (int y = 0; y < pDoc->m_height; y++)
		{
			for (int x = 0; x < pDoc->m_width; x++)
			{
				pDC->SetPixel(x, y, RGB(pDoc->m_OpenImg[y][x][0], pDoc->m_OpenImg[y][x][1], pDoc->m_OpenImg[y][x][2]));

			}
		}  // Input image �׸���

		if (pDoc->transform == 1)
		{
			for (int y = 0; y < pDoc->m_height; y++)
			{
				for (int x = 0; x < pDoc->m_width; x++)
				{
					pDC->SetPixel(x + pDoc->m_width + 10, y, RGB(pDoc->m_ResultImg[y][x][0], pDoc->m_ResultImg[y][x][1], pDoc->m_ResultImg[y][x][2]));
				}
			}  // K-means ��� �׸���
		}

		if (pDoc->transform == 2)
		{
			for (int y = 0; y < pDoc->m_height; y++)
			{
				for (int x = 0; x < pDoc->m_width; x++)
				{
					R = G = B = pDoc->m_ResultImg[y][x][0];
					pDC->SetPixel(x + pDoc->m_width + 10, y, RGB(R, G, B));
					R = G = B = pDoc->m_ResultImg[y][x][1];
					pDC->SetPixel(x, y + pDoc->m_height + 10, RGB(R, G, B));
					R = G = B = pDoc->m_ResultImg[y][x][2];
					pDC->SetPixel(x + pDoc->m_width + 10, y + pDoc->m_height + 10, RGB(R, G, B));
				}
			}  // HSI , RGB �� ä�� �׸���.
		}
	}


	// CPoposhopColorView �μ�

	BOOL CPoposhopColorView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// �⺻���� �غ�
		return DoPreparePrinting(pInfo);
	}

	void CPoposhopColorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	}

	void CPoposhopColorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
	}


	// CPoposhopColorView ����

#ifdef _DEBUG
	void CPoposhopColorView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CPoposhopColorView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CPoposhopColorDoc* CPoposhopColorView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoposhopColorDoc)));
		return (CPoposhopColorDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CPoposhopColorView �޽��� ó����


	void CPoposhopColorView::OnToHsi()
	{
		// TODO: Add your command handler code here
		CPoposhopColorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->transform = 2;
		pDoc->haveColor = 1;
		pDoc->OnToHsi();

		Invalidate(TRUE);
	}


	void CPoposhopColorView::OnToRgb()
	{
		// TODO: Add your command handler code here
		CPoposhopColorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnToRgb();
		Invalidate(TRUE);
	}


	void CPoposhopColorView::OnMenuLightcompensation()
	{
		// TODO: Add your command handler code here
		CPoposhopColorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->transform = 1;
		pDoc->OnMenuLightcompensation();
		Invalidate(TRUE);
	}


	void CPoposhopColorView::OnMenuKMeans()
	{
		// TODO: Add your command handler code here
		CPoposhopColorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->transform = 1;
		pDoc->OnMenuKMeans();
		Invalidate(TRUE);

	}


	void CPoposhopColorView::OnMenuEqualization()
	{
		// TODO: Add your command handler code here

		CPoposhopColorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnMenuEqualization();
		Invalidate(TRUE);
	}


	void CPoposhopColorView::OnMenuKuwahara()
	{
		// TODO: Add your command handler code here
		CPoposhopColorDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMenuKuwahara();
		Invalidate(TRUE);
	}
