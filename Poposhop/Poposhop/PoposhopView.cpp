
// PoposhopView.cpp : CPoposhopView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Poposhop.h"
#endif

#include "PoposhopDoc.h"
#include "PoposhopView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPoposhopView

IMPLEMENT_DYNCREATE(CPoposhopView, CView)

	BEGIN_MESSAGE_MAP(CPoposhopView, CView)
		// 표준 인쇄 명령입니다.
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_COMMAND(ID_Menu_Down_Sampling, &CPoposhopView::OnMenuDownSampling)
		ON_COMMAND(ID_Menu_Up_Sampling, &CPoposhopView::OnMenuUpSampling)
		ON_COMMAND(ID_Menu_Quantization, &CPoposhopView::OnMenuQuantization)
		ON_COMMAND(ID_SUM_CONSTANT, &CPoposhopView::OnSumConstant)
		ON_COMMAND(ID_SUM_CONSTANT, &CPoposhopView::OnSumConstant)
		ON_COMMAND(ID_SUB_CONSTANT, &CPoposhopView::OnSubConstant)
		ON_COMMAND(ID_MUL_CONSTANT, &CPoposhopView::OnMulConstant)
		ON_COMMAND(ID_DIV_CONSTANT, &CPoposhopView::OnDivConstant)
		ON_COMMAND(ID_NEGA_TRANSFORM, &CPoposhopView::OnNegaTransform)
		ON_COMMAND(ID_GAMMA_CORRECTION, &CPoposhopView::OnGammaCorrection)
		ON_COMMAND(ID_BINARIZATION, &CPoposhopView::OnBinarization)
		ON_COMMAND(ID_MAX_MIN, &CPoposhopView::OnMaxMin)
		ON_COMMAND(ID_AVG, &CPoposhopView::OnAvg)
		ON_WM_MOUSEMOVE()
		ON_COMMAND(ID_HISTOGRAM, &CPoposhopView::OnHistogram)
		ON_COMMAND(ID_HISTO_STRETCH, &CPoposhopView::OnHistoStretch)
		ON_COMMAND(ID_HISTO_EQUAL, &CPoposhopView::OnHistoEqual)
		ON_COMMAND(ID_EMBOSSING, &CPoposhopView::OnEmbossing)
		ON_COMMAND(ID_EMBOSSING, &CPoposhopView::OnEmbossing)
		ON_COMMAND(ID_BLURR, &CPoposhopView::OnBlurr)
		ON_COMMAND(ID_GAUSSIAN_FILTER, &CPoposhopView::OnGaussianFilter)
		ON_COMMAND(ID_SHARPENING, &CPoposhopView::OnSharpening)
		ON_COMMAND(ID_MEDIAN_FILTER, &CPoposhopView::OnMedianFilter)
		ON_COMMAND(ID_NEAREST, &CPoposhopView::OnNearest)
		ON_COMMAND(ID_Bilinear, &CPoposhopView::OnBilinear)
		ON_COMMAND(ID_MEDIANSUB, &CPoposhopView::OnMediansub)
		ON_COMMAND(ID_MEANSUB, &CPoposhopView::OnMeansub)
		ON_COMMAND(ID_TRANSLATION, &CPoposhopView::OnTranslation)
		ON_COMMAND(ID_MIRRORHOR, &CPoposhopView::OnMirrorhor)
		ON_COMMAND(ID_ROTATION, &CPoposhopView::OnRotation)
		ON_COMMAND(ID_KUWFILTER, &CPoposhopView::OnKuwfilter)
	END_MESSAGE_MAP()

	// CPoposhopView 생성/소멸

	CPoposhopView::CPoposhopView()
	{
		// TODO: 여기에 생성 코드를 추가합니다.

	}

	CPoposhopView::~CPoposhopView()
	{
	}

	BOOL CPoposhopView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: CREATESTRUCT cs를 수정하여 여기에서
		//  Window 클래스 또는 스타일을 수정합니다.

		return CView::PreCreateWindow(cs);
	}

	// CPoposhopView 그리기

	void CPoposhopView::OnDraw(CDC* pDC)
	{
		CPoposhopDoc* pDoc = GetDocument();


		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		int i, j;
		unsigned char R, G , B;

		for(i=0 ; i<pDoc->m_height; i++){
			for(j=0 ; j<pDoc->m_width; j++){
				R = G = B = pDoc->m_InputImage[i*pDoc->m_width+j];
				pDC->SetPixel(j+5, i+5, RGB(R, G, B));
			}
		}

		for(i=0 ; i<pDoc->m_Re_height; i++){
			for(j=0 ; j<pDoc->m_Re_width; j++){
				R = G = B = pDoc->m_OutputImage[i*pDoc->m_Re_width+j];
				pDC->SetPixel(j+pDoc->m_width+10, i+5, RGB(R, G, B));
			}
		}


		// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	}


	// CPoposhopView 인쇄

	BOOL CPoposhopView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 기본적인 준비
		return DoPreparePrinting(pInfo);
	}

	void CPoposhopView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
	}

	void CPoposhopView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 인쇄 후 정리 작업을 추가합니다.
	}

	// CPoposhopView 진단

#ifdef _DEBUG
	void CPoposhopView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CPoposhopView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CPoposhopDoc* CPoposhopView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPoposhopDoc)));
		return (CPoposhopDoc*)m_pDocument;
	}
#endif //_DEBUG

	// CPoposhopView 메시지 처리기

	void CPoposhopView::OnMenuDownSampling()
	{
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnDownSampling();
		Invalidate(TRUE);

	}

	void CPoposhopView::OnMenuUpSampling()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnUpSampling();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnMenuQuantization()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnQuantization();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnSumConstant()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnSumConstant();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnSubConstant()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnSubConstant();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnMulConstant()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnMulConstant();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnDivConstant()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnDivConstant();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnNegaTransform()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnNegaTransform();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnGammaCorrection()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnGammaCorrection();

		Invalidate(TRUE);
	}

	void CPoposhopView::OnBinarization()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnBinarization();
		Invalidate(TRUE);
	}

	void CPoposhopView::OnMaxMin()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMaxmin();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnAvg()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc * pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnAvg();
		Invalidate(TRUE);
	}

	void CPoposhopView::OnMouseMove(UINT nFlags, CPoint point)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CPoposhopDoc* pDoc = GetDocument();

		CStatusBar* pStatus = pFrame->GetStatusBar();

		CString strInfo;

		CRect rect;
		GetClientRect(&rect);

		if (point.x < 0 || point.x >= pDoc->m_width ||
			point.y < 0 || point.y >= pDoc->m_height)
		{
			// 현재 윈도우 안으로 커서가 빠져나갔다.
			pStatus->SetPaneText(1, TEXT(""));
		}
		else
		{
			// 현재 윈도우 안으로 커서가 들어왔다.
			strInfo.Format(TEXT("X:%3d, Y:%3d 픽셀:%3d"), point.x, point.y,pDoc->m_InputImage[point.x]);
			pStatus->SetPaneText(0, strInfo);	
		}
	}

	void CPoposhopView::OnHistogram()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc *pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnHistogram();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnHistoStretch()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnHistoStretch();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnHistoEqual()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnHistoEqual();
		Invalidate(TRUE);
	}



	void CPoposhopView::OnEmbossing()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnEmbossing();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnBlurr()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnBlurr();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnGaussianFilter()
	{
		// TODO: Add your command handler code here

		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnGaussianFilter();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnSharpening()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnSharpening();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnMedianFilter()
	{
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMedianFilter();
		Invalidate(TRUE);
	}

	void CPoposhopView::OnNearest()
	{
		// TODO: Add your command handler code here

		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnNearest();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnBilinear()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnBilinear();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnMediansub()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMediansub();
		Invalidate(TRUE);

	}


	void CPoposhopView::OnMeansub()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMeansub();
		Invalidate(TRUE);

	}


	void CPoposhopView::OnTranslation()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnTranslation();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnMirrorhor()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnMirrorhor();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnRotation()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->OnRotation();
		Invalidate(TRUE);
	}


	void CPoposhopView::OnKuwfilter()
	{
		// TODO: Add your command handler code here
		CPoposhopDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);

		pDoc->OnKuwFilter();

		Invalidate(TRUE);

	}
