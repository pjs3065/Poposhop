
// PoposhopColorView.cpp : CPoposhopColorView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
		// 표준 인쇄 명령입니다.
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

	// CPoposhopColorView 생성/소멸

	CPoposhopColorView::CPoposhopColorView()
	{
		// TODO: 여기에 생성 코드를 추가합니다.

	}

	CPoposhopColorView::~CPoposhopColorView()
	{
	}

	BOOL CPoposhopColorView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// CPoposhopColorView 그리기

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
		}  // Input image 그리기

		if (pDoc->transform == 1)
		{
			for (int y = 0; y < pDoc->m_height; y++)
			{
				for (int x = 0; x < pDoc->m_width; x++)
				{
					pDC->SetPixel(x + pDoc->m_width + 10, y, RGB(pDoc->m_ResultImg[y][x][0], pDoc->m_ResultImg[y][x][1], pDoc->m_ResultImg[y][x][2]));
				}
			}  // K-means 결과 그리기
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
			}  // HSI , RGB 각 채널 그리기.
		}
	}


	// CPoposhopColorView 인쇄

	BOOL CPoposhopColorView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void CPoposhopColorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void CPoposhopColorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}


	// CPoposhopColorView 진단

#ifdef _DEBUG
	void CPoposhopColorView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CPoposhopColorView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CPoposhopColorDoc* CPoposhopColorView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoposhopColorDoc)));
		return (CPoposhopColorDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CPoposhopColorView 메시지 처리기


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
