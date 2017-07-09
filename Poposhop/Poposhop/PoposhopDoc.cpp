
// PoposhopDoc.cpp : CPoposhopDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Poposhop.h"
#endif

#include "PoposhopDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPoposhopDoc

IMPLEMENT_DYNCREATE(CPoposhopDoc, CDocument)

	BEGIN_MESSAGE_MAP(CPoposhopDoc, CDocument)
	END_MESSAGE_MAP()


	// CPoposhopDoc 생성/소멸

	CPoposhopDoc::CPoposhopDoc()
		: m_InputImage(0)
		, m_width(0)
		, m_height(0)
		, m_size(0)
		, m_OutputImage(0)
		, m_Re_width(0)
		, m_Re_height(0)
		, m_Re_size(0)
	{
		// TODO: 여기에 일회성 생성 코드를 추가합니다.

	}

	CPoposhopDoc::~CPoposhopDoc()
	{
	}

	//BOOL CPoposhopDoc::OnNewDocument()
	//{
	//	if (!CDocument::OnNewDocument())
	//		return FALSE;
	//
	//	// TODO: 여기에 재초기화 코드를 추가합니다.
	//	// SDI 문서는 이 문서를 다시 사용합니다.
	//
	//	return TRUE;
	//}




	// CPoposhopDoc serialization

	void CPoposhopDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: 여기에 저장 코드를 추가합니다.
		}
		else
		{
			// TODO: 여기에 로딩 코드를 추가합니다.
		}
	}

#ifdef SHARED_HANDLERS

	// 축소판 그림을 지원합니다.
	void CPoposhopDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
		dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

		CString strText = _T("TODO: implement thumbnail drawing here");
		LOGFONT lf;

		CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
		pDefaultGUIFont->GetLogFont(&lf);
		lf.lfHeight = 36;

		CFont fontDraw;
		fontDraw.CreateFontIndirect(&lf);

		CFont* pOldFont = dc.SelectObject(&fontDraw);
		dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
		dc.SelectObject(pOldFont);
	}

	// 검색 처리기를 지원합니다.
	void CPoposhopDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
		// 콘텐츠 부분은 ";"로 구분되어야 합니다.

		// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
		SetSearchContent(strSearchContent);
	}

	void CPoposhopDoc::SetSearchContent(const CString& value)
	{
		if (value.IsEmpty())
		{
			RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
		}
		else
		{
			CMFCFilterChunkValueImpl *pChunk = NULL;
			ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
			if (pChunk != NULL)
			{
				pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
				SetChunkValue(pChunk);
			}
		}
	}

#endif // SHARED_HANDLERS

	// CPoposhopDoc 진단

#ifdef _DEBUG
	void CPoposhopDoc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void CPoposhopDoc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// CPoposhopDoc 명령

	/*
	BOOL CPoposhopDoc::OnOpenDocument(LPCTSTR lpszPathName)

	*/



	BOOL CPoposhopDoc::OnNewDocument()
	{
		// TODO: Add your specialized code here and/or call the base class

		return CDocument::OnNewDocument();
	}


	BOOL CPoposhopDoc::OnOpenDocument(LPCTSTR lpszPathName)
	{
		if (!CDocument::OnOpenDocument(lpszPathName))
			return FALSE;

		CFile File; // 파일객체선언

		File.Open(lpszPathName, CFile::modeRead| CFile::typeBinary);

		// 파일열기대화상자에서선택한파일을지정하고읽기모드선택
		// 이책에서는영상의크기256*256, 512*512, 640*480만을사용한다.

		if(File.GetLength() == 256*256){ // RAW 파일의크기결정
			m_height= 256;
			m_width= 256;
		}

		else if(File.GetLength() == 512*512){ // RAW 파일의크기결정
			m_height= 512;
			m_width= 512;
		}

		else if(File.GetLength() == 640*480){ // RAW 파일의크기결정
			m_height= 480;
			m_width= 640;
		}

		else{
			AfxMessageBox("Not Support Image Size"); // 해당크기가없는경우
			return 0;
		}
		m_size= m_width* m_height; // 영상의크기계산
		m_InputImage = new unsigned char [m_size];

		// 입력영상의크기에맞는메모리할당
		for(int i= 0 ; i<m_size; i++)
			m_InputImage[i] = 255; // 초기화

		File.Read(m_InputImage, m_size); // 입력영상파일읽기
		File.Close(); // 파일닫기

		return TRUE;
	}

	BOOL CPoposhopDoc::OnSaveDocument(LPCTSTR lpszPathName)
	{
		CFile File; // 파일객체선언
		File.Open(lpszPathName, CFile::modeCreate| CFile::modeWrite);
		File.Write(m_OutputImage, m_Re_size); // 파일쓰기
		File.Close(); // 파일닫기
		return true;
	}


	void CPoposhopDoc::OnDownSampling(void)
	{
		int i, j;
		CSamplingDig dlg;
		if(dlg.DoModal() == IDOK)
		{
			m_Re_height = m_height / dlg.m_SamplingRate;
			m_Re_width = m_width / dlg.m_SamplingRate;
			m_Re_size = m_Re_height * m_Re_width;
			m_OutputImage = new unsigned char [m_Re_size];

			for(i=0; i<m_Re_height ; i++)
			{
				for(j=0; j<m_Re_width; j++)
				{
					m_OutputImage[i*m_Re_width + j] = m_InputImage[(i*dlg.m_SamplingRate *m_width) + dlg.m_SamplingRate*j];
				}
			}
		}
	}


	void CPoposhopDoc::OnUpSampling(void)
	{
		int i, j;
		CSamplingDig dlg;
		if(dlg.DoModal() == IDOK)
		{
			m_Re_height = m_height * dlg.m_SamplingRate;
			m_Re_width = m_width * dlg.m_SamplingRate;
			m_Re_size = m_Re_height * m_Re_width;

			m_OutputImage = new unsigned char [m_Re_size];

			for(i=0; i<m_Re_size; i++)
			{
				m_OutputImage[i] = 255;
			}

			for(i=0; i<m_height ; i++)
			{
				for(j=0; j<m_width; j++)
				{
					m_OutputImage[(i*dlg.m_SamplingRate *m_Re_width) + dlg.m_SamplingRate*j] = m_InputImage[i*m_width + j];
				}
			}
		}
	}


	void CPoposhopDoc::OnQuantization(void)
	{
		CQuantizationDlg dlg;
		if(dlg.DoModal() == IDOK)

		{
			int i, j, value, LEVEL;
			double HIGH, *TEMP;

			m_Re_height= m_height;
			m_Re_width= m_width;
			m_Re_size= m_Re_height* m_Re_width;

			m_OutputImage= new unsigned char[m_Re_size];

			TEMP = new double [m_size];

			LEVEL=256; 
			HIGH=256.;
			value = (int)pow(2, dlg.m_QuantBit);

			for(i=0 ; i<m_size; i++){
				for(j=0 ; j<value ; j++){
					if(m_InputImage[i] >=(LEVEL/value)*j &&
						m_InputImage[i]<(LEVEL/value)*(j+1)){
							TEMP[i]=(double)(HIGH/value)*j; 
					}
				}
			}
			for(i=0 ; i<m_size; i++){
				m_OutputImage[i] = (unsigned char)TEMP[i];
			}
		}
	}


	void CPoposhopDoc::OnSumConstant(void)
	{
		CConstantDlg dlg; // 상수값을입력받는대화상자
		int i;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		if(dlg.DoModal() == IDOK){
			for(i=0 ; i<m_size ; i++){
				if(m_InputImage[i] + dlg.m_Constant >= 255)
					m_OutputImage[i] = 255;
				// 출력값이255보다크면255 출력
				else
					m_OutputImage[i]=(unsigned char)(m_InputImage[i] + dlg.m_Constant);
				// 상수값과화소값과의덧셈
			}
		}
	}


	void CPoposhopDoc::OnSubConstant(void)
	{
		CConstantDlg dlg;
		int i;
		m_Re_height= m_height;
		m_Re_width= m_width;
		m_Re_size= m_Re_height* m_Re_width;
		m_OutputImage= new unsigned char[m_Re_size];
		if(dlg.DoModal() == IDOK){
			for(i=0 ; i<m_size; i++){
				if(m_InputImage[i] -dlg.m_Constant< 0)
					m_OutputImage[i] = 0; // 출력값이0보다작으면0 출력
				else
					m_OutputImage[i] = (unsigned char)(m_InputImage[i] -dlg.m_Constant);
				// 상수값과화소값과의뺄셈
			}
		}
	}


	void CPoposhopDoc::OnMulConstant(void)
	{
		CConstantDlg dlg;
		int i;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		if(dlg.DoModal() == IDOK){
			for(i=0 ; i<m_size ; i++){
				if(m_InputImage[i] * dlg.m_Constant > 255)
					m_OutputImage[i] = 255;
				// 곱의값이255보다크면255를출력
				else if(m_InputImage[i] * dlg.m_Constant < 0)
					m_OutputImage[i] = 0;
				// 곱의값이0보다작으면0을출력
				else
					m_OutputImage [i]
				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
				// 상수값과화소값곱셈
			}
		}
	}


	void CPoposhopDoc::OnDivConstant(void)
	{
		CConstantDlg dlg;
		int i;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		if(dlg.DoModal() == IDOK){
			for(i=0 ; i<m_size ; i++){
				if(m_InputImage[i] / dlg.m_Constant > 255)
					m_OutputImage[i] = 255;
				// 나눗셈의값이255보다크면255를출력
				else if(m_InputImage[i] / dlg.m_Constant < 0)
					m_OutputImage[i] = 0;
				// 나눗셈의값이0보다작으면0을출력
				else
					m_OutputImage [i]
				= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
				// 상수값과화소값나눗셈
			}
		}
	}

	void CPoposhopDoc::OnNegaTransform(void)
	{
		int i;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		for(i=0 ; i<m_size ; i++)
			m_OutputImage[i] = 255 - m_InputImage[i]; // 영상반전을수행
	}


	void CPoposhopDoc::OnGammaCorrection(void)
	{
		CConstantDlg dlg;
		int i;
		//double temp;
		unsigned char LUT[256];

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		if(dlg.DoModal() == IDOK){
			/*
			for(i=0 ; i<m_size ; i++){
			temp = pow(m_InputImage[i], 1/dlg.m_Constant);
			// 감마값계산
			if(temp < 0)
			m_OutputImage[i] = 0;
			else if(temp > 255)
			m_OutputImage[i] = 255;
			else
			m_OutputImage[i] = (unsigned char)temp;
			}*/
			for (i = 0; i < 256;i++) {
				int temp = (int)(i*1.5);
				LUT[i] = temp > 255 ? 255 : temp;
			}

			for (i = 0; i < m_size;i++)
			{
				m_OutputImage[i] = LUT[m_InputImage[i]];
			}

		}
	}

	void CPoposhopDoc::OnBinarization(void)
	{
		CConstantDlg dlg;
		int i;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];
		if(dlg.DoModal() == IDOK){
			for(i=0 ; i<m_size ; i++){
				if(m_InputImage[i] >= dlg.m_Constant)
					m_OutputImage[i] = 255; // 임계값보다크면255 출력
				else
					m_OutputImage[i] = 0; // 임계값보다작으면0 출력
			}
		}
	}


	void CPoposhopDoc::OnMaxmin(void)
	{
		CMaxminDlg dc;

		int i;
		unsigned char LOW, HIGH, MAX, MIN;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		LOW = 0;
		HIGH = 255;

		MIN = m_InputImage[0]; // 최소값을 찾기 위한 초기값
		MAX = m_InputImage[0]; // 최대값을 찾기 위한 초기값

		// 입력 영상의 최소값 찾기
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] < MIN)
				MIN = m_InputImage[i];
		}

		// 입력 영상의 최대값 찾기
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] > MAX)
				MAX = m_InputImage[i];
		}

		CString szText;

		szText.Format(TEXT("최솟값은 %d입니다.\n최대값은 %d입니다."), MIN, MAX);

		dc.MessageBox(szText);


	}


	void CPoposhopDoc::OnAvg(void)
	{
		CAvgDlg dc;

		int i;
		double SUM, AVG;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		SUM = m_InputImage[0]; 

		for (i = 0; i < m_size; i++) {

			SUM += m_InputImage[i];
		}

		AVG = ((double)SUM) / m_size;

		CString szText;
		szText.Format(TEXT("평균값값은 %.2f 입니다."), AVG);

		dc.MessageBox(szText);
	}


	void CPoposhopDoc::OnHistogram(void)
	{
		int i, j;
		int MAX;
		int Histo[256];

		//히스토그램 크기
		m_Re_height = 256;
		m_Re_width = 256;
		m_Re_size = m_Re_height * m_Re_width;

		//초기화
		for(i= 0; i<256; i++)
			Histo[i] = 0;

		//빈도수 조사
		for(i=0; i<m_size ; i++){
			Histo[m_InputImage[i]]++;
		}

		//정규화
		MAX = Histo[0];

		for(i=0; i<256; i++)
		{
			if(Histo[i] > MAX)
				MAX = Histo[i];
		}

		//정규화된 히스토그램
		for(i=0; i<256; i++)
			Histo[i] = (int)(Histo[i] * 255 / MAX);
		m_OutputImage = new unsigned char[m_Re_size+(256*20)];

		//히스토그램 출력
		for(i=0; i<m_Re_size; i++)
			m_OutputImage[i] = 255;

		for(i=0; i<256; i++){
			for(j=0; j<Histo[i]; j++)
			{
				m_OutputImage[m_Re_width*(m_Re_height-j-1) +i] = 0;
			}
		}

		for(i= m_Re_height ; i<m_Re_height + 5; i++)
		{
			for(j=0; j<256; j++){
				m_OutputImage[m_Re_height*i +j] =255;
			}
		}
		for(i= m_Re_height+5; i<m_Re_height+20; i++)
		{
			for(j=0; j<256; j++)
			{
				m_OutputImage[m_Re_height * i +j] = j;
			}
		}

		m_Re_height = m_Re_height + 20;
		m_Re_size = m_Re_height * m_Re_width;
	}


	void CPoposhopDoc::OnHistoStretch(void)
	{
		int i;
		unsigned char LOW, HIGH, MAX, MIN;
		m_Re_height= m_height;
		m_Re_width= m_width;
		m_Re_size= m_Re_height* m_Re_width;
		LOW = 0;
		HIGH = 255;
		MIN = m_InputImage[0]; // 최소값을찾기위한초기값
		MAX = m_InputImage[0]; // 최대값을찾기위한초기값
		// 입력영상의최소값찾기
		for(i=0 ; i<m_size; i++){
			if(m_InputImage[i] < MIN)
				MIN = m_InputImage[i];
		}
		// 입력영상의최대값찾기
		for(i=0 ; i<m_size; i++){
			if(m_InputImage[i] > MAX)
				MAX = m_InputImage[i];
		}
		m_OutputImage= new unsigned char[m_Re_size];
		// 히스토그램stretch
		for(i=0 ; i<m_size; i++)
			m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN)*HIGH / (MAX-MIN));
	}


	void CPoposhopDoc::OnHistoEqual(void)
	{
		int i, value;
		unsigned char LOW, HIGH, Temp;
		double SUM = 0.0;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		LOW = 0;
		HIGH = 255;
		// 초기화
		for (i = 0; i<256; i++)
			m_HIST[i] = LOW;
		// 빈도수조사
		for (i = 0; i<m_size; i++) {
			value = (int)m_InputImage[i];
			m_HIST[value]++;
		}
		// 누적히스토그램생성
		for (i = 0; i<256; i++) {
			SUM += m_HIST[i];
			m_Sum_Of_HIST[i] = SUM;
		}
		m_OutputImage = new unsigned char[m_Re_size];
		// 입력영상을평활화된영상으로출력
		for (i = 0; i<m_size; i++) {
			Temp = m_InputImage[i];
			m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
		}
	}


	void CPoposhopDoc::OnEmbossing(void)
	{
		int i,j;
		double EmboMask[3][3] = {{-1.,0.,0.}, {0., 0., 0.}, {0., 0., 1.}};

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		m_tempImage = OnMaskProcess(m_InputImage, EmboMask);
		// OnMaskProcess 함수를호출하여회선처리를한다.


		/*
		for(i=0 ; i<m_Re_height ; i++){
		for(j=0 ; j<m_Re_width ; j++){
		if(m_tempImage[i][j] > 255.)
		m_tempImage[i][j] = 255.;
		if(m_tempImage[i][j] < 0.)
		m_tempImage[i][j] = 0.;
		}

		} // 회선처리결과가0~255 사이값이되도록한다.
		*/

		// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
		// 정규화함수를사용할때
		// 회선처리결과나정규화처리결과는2차원배열값이되므로
		// 2차원배열을1차원배열로바꾸어출력하도록한다.

		for(i=0 ; i<m_Re_height ; i++){
			for(j=0 ; j<m_Re_width ; j++){
				m_OutputImage[i*m_Re_width + j]
				= (unsigned char)(m_tempImage[i][j] + 128);
			}
		}
	}


	double** CPoposhopDoc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
	{
		// 회선처리가일어나는함수
		int i, j, n, m;
		double **tempInputImage, **tempOutputImage, S = 0.0;
		tempInputImage = Image2DMem(m_height + 2, m_width + 2);
		// 입력값을위한메모리할당
		tempOutputImage = Image2DMem(m_height, m_width);
		// 출력값을위한메모리할당
		// 1차원입력영상의값을2차원배열에할당한다.
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				tempInputImage[i+1][j+1]
				= (double)Target[i * m_width + j];
			}
		}
		// 회선연산
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				for(n=0 ; n<3 ; n++){
					for(m=0 ; m<3 ; m++){
						S += Mask[n][m] * tempInputImage[i+n][j+m];
					}
				} // 회선마스크의크기만큼이동하면서값을누적
				tempOutputImage[i][j] = S; // 누적된값을출력메모리에저장
				S = 0.0; // 다음블록으로이동하면누적값을초기화
			}
		}
		return tempOutputImage; // 결과값반환
	}


	double** CPoposhopDoc::OnScale(double **Target, int height, int width)
	{
		// 정규화를위한함수
		int i, j;
		double min, max;
		min = max = Target[0][0];
		for(i=0 ; i<height ; i++){
			for(j=0 ; j<width ; j++){
				if(Target[i][j] <= min)
					min = Target[i][j];
			}
		}
		for(i=0 ; i<height ; i++){
			for(j=0 ; j<width ; j++){
				if(Target[i][j] >= max)
					max = Target[i][j];
			}
		}
		max = max -min;
		for(i=0 ; i<height ; i++){
			for(j=0 ; j<width ; j++){
				Target[i][j] = (Target[i][j] -min) * (255. / max);
			}
		}
		return Target;
	}


	double** CPoposhopDoc::Image2DMem(int height, int width)
	{
		double** temp;
		int i, j;
		temp = new double *[height];
		for(i=0 ; i<height ; i++){
			temp[i] = new double [width];
		}
		for(i=0 ; i<height ; i++){
			for(j=0 ; j<width ; j++){
				temp[i][j] = 0.0;
			}
		} // 할당된2차원메모리를초기화
		return temp;
	}


	void CPoposhopDoc::OnBlurr(void)
	{
		int i, j;
		double BlurrMask[3][3] = {{1./9., 1./9., 1./9.},
		{1./9., 1./9., 1./9.}, {1./9., 1./9., 1./9.}};
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);
		// 블러링처리
		// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
		// 정규화
		for(i=0 ; i<m_Re_height ; i++){
			for(j=0 ; j<m_Re_width ; j++){
				if(m_tempImage[i][j] > 255.)
					m_tempImage[i][j] = 255.;
				if(m_tempImage[i][j] < 0.)
					m_tempImage[i][j] = 0.;
			}
		}
		for(i=0 ; i<m_Re_height ; i++){
			for(j=0 ; j<m_Re_width ; j++){
				m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
			}
		}
	}


	void CPoposhopDoc::OnGaussianFilter(void)
	{
		int i, j;
		double GaussianMask[3][3] = {{1./16., 1./8., 1./16.},
		{1./8., 1./4., 1./8.}, {1./16., 1./8., 1./16.}};

		m_Re_height= m_height;
		m_Re_width= m_width;
		m_Re_size= m_Re_height* m_Re_width;
		m_OutputImage= new unsigned char [m_Re_size];
		m_tempImage= OnMaskProcess(m_InputImage, GaussianMask);
		// m_tempImage= OnScale(m_tempImage, m_Re_height, m_Re_width);

		for(i=0 ; i<m_Re_height; i++){
			for(j=0 ; j<m_Re_width; j++){
				if(m_tempImage[i][j] > 255.)
					m_tempImage[i][j] = 255.;
				if(m_tempImage[i][j] < 0.)
					m_tempImage[i][j] = 0.;
			}
		}

		for(i=0 ; i<m_Re_height; i++){
			for(j=0 ; j<m_Re_width; j++){
				m_OutputImage[i*m_Re_width+ j]
				= (unsigned char)m_tempImage[i][j];
			}
		}
	}


	void CPoposhopDoc::OnSharpening(void)
	{
		int i, j;
		//double SharpeningMask[3][3] = {{-1., -1., -1.},{-1., 9., -1.}, {-1., -1., -1.}};
		double SharpeningMask[3][3] = {{0., -1., 0.}, {-1., 5.,
			-1.}, {0., -1., 0.}};

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);

		// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

		for(i=0 ; i<m_Re_height ; i++){
			for(j=0 ; j<m_Re_width ; j++){
				if(m_tempImage[i][j] > 255.)
					m_tempImage[i][j] = 255.;
				if(m_tempImage[i][j] < 0.)
					m_tempImage[i][j] = 0.;
			}
		}

		for(i=0 ; i<m_Re_height ; i++){
			for(j=0 ; j<m_Re_width ; j++){
				m_OutputImage[i*m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
			}
		}
	}



	void CPoposhopDoc::OnMedianFilter(void)
	{
		int i, j, n, m, index = 0;
		double **tempInputImage, Mask[9];

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];

		tempInputImage = Image2DMem(m_height + 2, m_width + 2);

		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				tempInputImage[i+1][j+1]
				= (double)m_InputImage[i * m_width + j];
			}
		}

		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				for(n=0 ; n<3 ; n++){
					for(m=0 ; m<3 ; m++){
						Mask[n*3 + m] = tempInputImage[i+n][j+m];
						// 3*3 크기배열값을마스크배열에할당
					}
				}
				OnBubleSort(Mask, 9); // 마스크값을크기순으로정렬
				m_OutputImage[index] = (unsigned char)Mask[4];
				// 중간값출력
				index++; // 출력배열의좌표
			}
		}
	}

	void CPoposhopDoc::OnBubleSort(double* mask, int index)
	{
		double temp;
		for(int i = 0; i < index; i++)
		{
			for(int j = 0; j < index-1; j++)
			{
				if(mask[j] > mask[j+1])
				{
					temp = mask[j];
					mask[j] = mask[j+1];
					mask[j+1] = temp;
				}
			}
		}
	}

	void CPoposhopDoc::OnNearest(void)
	{
		CSamplingDig dlg;
		int i,j;
		//int ZoomRate = 2; // 영상확대배율
		double **tempArray;
		if(dlg.DoModal() == IDOK)
		{ 
			m_Re_height = int(dlg.m_SamplingRate * m_height); // 확대된영상의높이
			m_Re_width = int(dlg.m_SamplingRate * m_width); // 확대된영상의너비
			m_Re_size = m_Re_height * m_Re_width;
			m_tempImage = Image2DMem(m_height, m_width);
			tempArray = Image2DMem(m_Re_height, m_Re_width);

			m_OutputImage = new unsigned char [m_Re_size];
			for(i=0 ; i<m_height ; i++){
				for(j=0 ; j<m_width ; j++){
					m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
				}
			}
			for(i=0 ; i< m_Re_height ; i++){
				for(j=0 ; j< m_Re_width ; j++){
					tempArray[i][j] = m_tempImage[i/dlg.m_SamplingRate][j/dlg.m_SamplingRate];
					// 이웃한화소를이용한보간
				}
			}
			for(i=0 ; i< m_Re_height ; i++){
				for(j=0 ; j< m_Re_width ; j++){
					m_OutputImage[i* m_Re_width + j] = (unsigned char)tempArray[i][j];
				}
			}
		}
	}


	void CPoposhopDoc::OnBilinear(void)
	{
		int i, j, point, i_H, i_W;
		unsigned char newValue;
		//double ZoomRate = 2.0, 
		double r_H, r_W, s_H, s_W;
		double C1, C2, C3, C4;
		CSamplingDig dlg;


		if(dlg.DoModal() == IDOK)
		{ 
			m_Re_height = (int)(m_height * dlg.m_SamplingRate); // 확대된영상의높이
			m_Re_width = (int)(m_width * dlg.m_SamplingRate); // 확대된영상의너비
			m_Re_size = m_Re_height * m_Re_width;
			m_tempImage = Image2DMem(m_height, m_width);
			m_OutputImage = new unsigned char [m_Re_size];
			for(i=0 ; i<m_height ; i++){
				for(j=0 ; j<m_width ; j++){
					m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
				}
			}

			for(i=0 ; i< m_Re_height ; i++){
				for(j=0 ; j< m_Re_width ; j++){
					r_H = i / dlg.m_SamplingRate;
					r_W = j / dlg.m_SamplingRate;
					i_H = (int)floor(r_H);
					i_W = (int)floor(r_W);
					s_H = r_H -i_H;
					s_W = r_W -i_W;
					if(i_H < 0 || i_H >= (m_height-1) || i_W < 0
						|| i_W >= (m_width-1))
					{
						point = i* m_Re_width + j;
						m_OutputImage[point] = 255;
					}
					else
					{
						C1 = (double)m_tempImage[i_H][i_W];
						C2 = (double)m_tempImage[i_H][i_W+1];
						C3 = (double)m_tempImage[i_H+1][i_W+1];
						C4 = (double)m_tempImage[i_H+1][i_W];
						newValue = (unsigned char)(C1*(1-s_H)*(1-s_W)
							+C2*s_W*(1-s_H)+C3*s_W*s_H+C4*(1-s_W)*s_H);
						point = i* m_Re_width+j;
						m_OutputImage[point] = newValue;
					}
				}
			}
		}
	}

	void CPoposhopDoc::OnMediansub(void)
	{
		int i, j, n, m,index = 0; // M = 서브샘플링비율
		//int M = 2;
		CSamplingDig dlg;

		if(dlg.DoModal() == IDOK)
		{ 
			double *Mask, Value;
			Mask = new double [dlg.m_SamplingRate*dlg.m_SamplingRate]; // 마스크의크기결정
			m_Re_height = (m_height + 1) / dlg.m_SamplingRate;
			m_Re_width = (m_width + 1) / dlg.m_SamplingRate;
			m_Re_size = m_Re_height * m_Re_width;
			m_OutputImage = new unsigned char [m_Re_size];
			m_tempImage = Image2DMem(m_height + 1, m_width + 1);
			for(i=0 ; i<m_height ; i++){
				for(j=0 ; j<m_width ; j++){
					m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
				}
			}
			for(i=0 ; i<m_height-1 ; i=i+dlg.m_SamplingRate){
				for(j=0 ; j<m_width-1 ; j=j+dlg.m_SamplingRate){
					for(n=0 ; n<dlg.m_SamplingRate ; n++){
						for(m=0 ; m<dlg.m_SamplingRate ; m++){
							Mask[n*dlg.m_SamplingRate + m] = m_tempImage[i+n][j+m];
							// 입력영상을블록으로잘라마스크배열에저장
						}
					}
					OnBubleSort(Mask, dlg.m_SamplingRate*dlg.m_SamplingRate); // 마스크에저장된값을정렬
					Value = Mask[(int)(dlg.m_SamplingRate*dlg.m_SamplingRate/2)]; // 정렬된값중가운데값을선택
					m_OutputImage[index] = (unsigned char)Value;
					// 가운데값을출력
					index++;
				}
			}
		}
	}

	void CPoposhopDoc::OnMeansub(void)
	{
		int i, j, n, m, index = 0, k; // M = 서브샘플링비율
		//int M = 3;

		CSamplingDig dlg;

		if(dlg.DoModal() == IDOK)
		{ 
			double *Mask, Value, Sum = 0.0;
			Mask = new double [dlg.m_SamplingRate*dlg.m_SamplingRate];
			m_Re_height = (m_height + 1) / dlg.m_SamplingRate;
			m_Re_width = (m_width + 1) /dlg.m_SamplingRate;
			m_Re_size = m_Re_height * m_Re_width;
			m_OutputImage = new unsigned char [m_Re_size];
			m_tempImage = Image2DMem(m_height + 1, m_width + 1);
			for(i=0 ; i<m_height ; i++){
				for(j=0 ; j<m_width ; j++){
					m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
				}
			}

			for(i=0 ; i<m_height-1 ; i=i+dlg.m_SamplingRate){
				for(j=0 ; j<m_width-1 ; j=j+dlg.m_SamplingRate){
					for(n=0 ; n<dlg.m_SamplingRate ; n++){
						for(m=0 ; m<dlg.m_SamplingRate ; m++){
							Mask[n*dlg.m_SamplingRate + m] = m_tempImage[i+n][j+m];
						}
					}
					for(k=0 ; k<dlg.m_SamplingRate*dlg.m_SamplingRate ; k++)
						Sum = Sum + Mask[k];
					// 마스크에저장된값을누적
					Value = (Sum / (dlg.m_SamplingRate*dlg.m_SamplingRate)); // 평균을계산
					m_OutputImage[index] = (unsigned char)Value;
					// 평균값을출력
					index++;
					Sum = 0.0;
				}
			}
		}
	}


	void CPoposhopDoc::OnTranslation(void)
	{
		int i,j;
		int h_pos = 30, w_pos = 130;
		double **tempArray;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		m_tempImage = Image2DMem(m_height, m_width);

		tempArray = Image2DMem(m_Re_height, m_Re_width);

		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
			}
		}
		for(i=0 ; i<m_height -h_pos ; i++){
			for(j=0 ; j<m_width -w_pos ; j++){
				tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
				// 입력영상을h_pos, w_pos만큼이동
			}
		}
		for(i=0 ; i< m_Re_height ; i++){
			for(j=0 ; j< m_Re_width ; j++){
				m_OutputImage[i* m_Re_width + j]
				= (unsigned char)tempArray[i][j];
			}
		}
		delete [] m_tempImage;
		delete [] tempArray;
	}


	void CPoposhopDoc::OnMirrorhor(void)
	{
		int i,j;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				m_OutputImage[i*m_width + m_width - j - 1] =
					m_InputImage[i*m_width + j];
				// 입력 영상의 배열 값을 출력 영상을 위한
				// 배열의 수평축 뒷자리부터 저장
			}
		}
	}


	void CPoposhopDoc::OnRotation(void)
	{
		int i, j, CenterH, CenterW, newH, newW, degree = 45;
		// degree = 회전할 각도
		double Radian, PI, **tempArray, Value;
		m_Re_height = m_height; // 회전된 영상의 높이
		m_Re_width = m_width; // 회전된 영상의 너비
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		PI = 3.14159265358979; // 회전각을 위한 PI 값
		Radian = (double)degree*PI / 180.0;
		// degree 값을 radian으로 변경
		CenterH = m_height / 2; // 영상의 중심 좌표
		CenterW = m_width / 2; // 영상의 중심 좌표
		m_tempImage = Image2DMem(m_height, m_width);
		tempArray = Image2DMem(m_Re_height, m_Re_width);
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
			}
		}
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				// 회전 변환 행렬을 이용하여 회전하게 될 좌표 값 계산
				newH = (int)((i - CenterH)*cos(Radian) - (j - CenterW)*sin(Radian) + CenterH);
				newW = (int)((i - CenterH)*sin(Radian) + (j - CenterW)*cos(Radian) + CenterW);
				if(newH < 0 || newH >= m_height){
					// 회전된 좌표가 출력 영상을 위한 배열 값을 넘어갈 때
					Value = 0;
				}
				else if(newW < 0 || newW >= m_width){
					// 회전된 좌표가 출력 영상을 위한 배열 값을 넘어갈 때
					Value = 0;
				}
				else{
					Value = m_tempImage[newH][newW];
				}
				tempArray[i][j] = Value;
			}

		}

		for(i=0 ; i< m_Re_height ; i++){
			for(j=0 ; j< m_Re_width ; j++){
				m_OutputImage[i* m_Re_width + j]
				= (unsigned char)tempArray[i][j];
			}
		}
		delete [] m_tempImage;
		delete [] tempArray;

	}

	double getAvg(double mask[], int length)
	{
		double total = 0;
		for (int i = 0; i < length; i++)
			total += mask[i];
		return (total / length);
	}
	double getVariance(double mask[], int length)
	{
		double total = 0;
		double Avg = 0;
		double variance = 0;


		Avg = getAvg(mask, length);

		for (int i = 0; i < length; i++)
			variance = variance + (mask[i] * mask[i]);
		variance = (variance / 9) - (Avg*Avg);

		variance = variance * variance;

		return sqrt(variance);

	}


	double * OnDivideMask(double Og[], int length, int start)
	{
		double *Sub = new double[9];
		int subIndex = 0;
		for (int j = 0; j < 3; j++) {
			for (int i = (start + (j * 5)); i < (start + (j * 5)) + 3; i++)
			{
				Sub[subIndex] = Og[i];
				subIndex++;
			}
			if (subIndex == 9)
				break;
		}
		return Sub;
	}

	void CPoposhopDoc::OnKuwFilter(void)
	{
		int i, j, n, m, index = 0;
		double **tempInputImage, Mask[25];
		double *SubMask;
		double min = 100000000;
		int region = 0;
		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		tempInputImage = Image2DMem(m_height + 4, m_width + 4);

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				tempInputImage[i + 2][j + 2]
				= (double)m_InputImage[i * m_width + j];
			}
		}
		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				for (n = 0; n < 5; n++) {
					for (m = 0; m < 5; m++) {
						Mask[n * 5 + m] = tempInputImage[i + n][j + m];
						// 5*5 크기 배열 값을 마스크 배열에 할당
					}
				}
				min = 1000000000000;
				region = -1;

				SubMask = NULL;
				SubMask = OnDivideMask(Mask, 25, 0);
				if (min > getVariance(SubMask, 9))
				{
					min = getVariance(SubMask, 9);
					region = 0;
				}

				SubMask = NULL;
				SubMask = OnDivideMask(Mask, 25, 2);
				if (min > getVariance(SubMask, 9))
				{
					min = getVariance(SubMask, 9);
					region = 1;
				}

				SubMask = NULL;
				SubMask = OnDivideMask(Mask, 25, 10);
				if (min > getVariance(SubMask, 9))
				{
					min = getVariance(SubMask, 9);
					region = 2;
				}

				SubMask = NULL;
				SubMask = OnDivideMask(Mask, 25, 12);
				if (min > getVariance(SubMask, 9))
				{
					min = getVariance(SubMask, 9);
					region = 3;
				}
				SubMask = NULL;
				if (region == 0) SubMask = OnDivideMask(Mask, 25, 0);
				else if (region == 1) SubMask = OnDivideMask(Mask, 25, 2);
				else if (region == 2)   SubMask = OnDivideMask(Mask, 25, 10);
				else  SubMask = OnDivideMask(Mask, 25, 12);

				m_OutputImage[index] = (unsigned char)getAvg(SubMask, 9);
				// 평균 값 출력
				index++; // 출력 배열의 좌표
			}
		}

	}


