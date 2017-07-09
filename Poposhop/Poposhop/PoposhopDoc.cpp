
// PoposhopDoc.cpp : CPoposhopDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


	// CPoposhopDoc ����/�Ҹ�

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
		// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

	}

	CPoposhopDoc::~CPoposhopDoc()
	{
	}

	//BOOL CPoposhopDoc::OnNewDocument()
	//{
	//	if (!CDocument::OnNewDocument())
	//		return FALSE;
	//
	//	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	//	// SDI ������ �� ������ �ٽ� ����մϴ�.
	//
	//	return TRUE;
	//}




	// CPoposhopDoc serialization

	void CPoposhopDoc::Serialize(CArchive& ar)
	{
		if (ar.IsStoring())
		{
			// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
		}
		else
		{
			// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
		}
	}

#ifdef SHARED_HANDLERS

	// ����� �׸��� �����մϴ�.
	void CPoposhopDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
	{
		// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

	// �˻� ó���⸦ �����մϴ�.
	void CPoposhopDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// ������ �����Ϳ��� �˻� �������� �����մϴ�.
		// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

		// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

	// CPoposhopDoc ����

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


	// CPoposhopDoc ���

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

		CFile File; // ���ϰ�ü����

		File.Open(lpszPathName, CFile::modeRead| CFile::typeBinary);

		// ���Ͽ����ȭ���ڿ��������������������ϰ��б��弱��
		// ��å�����¿�����ũ��256*256, 512*512, 640*480��������Ѵ�.

		if(File.GetLength() == 256*256){ // RAW ������ũ�����
			m_height= 256;
			m_width= 256;
		}

		else if(File.GetLength() == 512*512){ // RAW ������ũ�����
			m_height= 512;
			m_width= 512;
		}

		else if(File.GetLength() == 640*480){ // RAW ������ũ�����
			m_height= 480;
			m_width= 640;
		}

		else{
			AfxMessageBox("Not Support Image Size"); // �ش�ũ�Ⱑ���°��
			return 0;
		}
		m_size= m_width* m_height; // ������ũ����
		m_InputImage = new unsigned char [m_size];

		// �Է¿�����ũ�⿡�´¸޸��Ҵ�
		for(int i= 0 ; i<m_size; i++)
			m_InputImage[i] = 255; // �ʱ�ȭ

		File.Read(m_InputImage, m_size); // �Է¿��������б�
		File.Close(); // ���ϴݱ�

		return TRUE;
	}

	BOOL CPoposhopDoc::OnSaveDocument(LPCTSTR lpszPathName)
	{
		CFile File; // ���ϰ�ü����
		File.Open(lpszPathName, CFile::modeCreate| CFile::modeWrite);
		File.Write(m_OutputImage, m_Re_size); // ���Ͼ���
		File.Close(); // ���ϴݱ�
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
		CConstantDlg dlg; // ��������Է¹޴´�ȭ����
		int i;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		if(dlg.DoModal() == IDOK){
			for(i=0 ; i<m_size ; i++){
				if(m_InputImage[i] + dlg.m_Constant >= 255)
					m_OutputImage[i] = 255;
				// ��°���255����ũ��255 ���
				else
					m_OutputImage[i]=(unsigned char)(m_InputImage[i] + dlg.m_Constant);
				// �������ȭ�Ұ����ǵ���
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
					m_OutputImage[i] = 0; // ��°���0����������0 ���
				else
					m_OutputImage[i] = (unsigned char)(m_InputImage[i] -dlg.m_Constant);
				// �������ȭ�Ұ����ǻ���
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
				// ���ǰ���255����ũ��255�����
				else if(m_InputImage[i] * dlg.m_Constant < 0)
					m_OutputImage[i] = 0;
				// ���ǰ���0����������0�����
				else
					m_OutputImage [i]
				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
				// �������ȭ�Ұ�����
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
				// �������ǰ���255����ũ��255�����
				else if(m_InputImage[i] / dlg.m_Constant < 0)
					m_OutputImage[i] = 0;
				// �������ǰ���0����������0�����
				else
					m_OutputImage [i]
				= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
				// �������ȭ�Ұ�������
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
			m_OutputImage[i] = 255 - m_InputImage[i]; // �������������
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
			// ���������
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
					m_OutputImage[i] = 255; // �Ӱ谪����ũ��255 ���
				else
					m_OutputImage[i] = 0; // �Ӱ谪����������0 ���
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

		MIN = m_InputImage[0]; // �ּҰ��� ã�� ���� �ʱⰪ
		MAX = m_InputImage[0]; // �ִ밪�� ã�� ���� �ʱⰪ

		// �Է� ������ �ּҰ� ã��
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] < MIN)
				MIN = m_InputImage[i];
		}

		// �Է� ������ �ִ밪 ã��
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] > MAX)
				MAX = m_InputImage[i];
		}

		CString szText;

		szText.Format(TEXT("�ּڰ��� %d�Դϴ�.\n�ִ밪�� %d�Դϴ�."), MIN, MAX);

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
		szText.Format(TEXT("��հ����� %.2f �Դϴ�."), AVG);

		dc.MessageBox(szText);
	}


	void CPoposhopDoc::OnHistogram(void)
	{
		int i, j;
		int MAX;
		int Histo[256];

		//������׷� ũ��
		m_Re_height = 256;
		m_Re_width = 256;
		m_Re_size = m_Re_height * m_Re_width;

		//�ʱ�ȭ
		for(i= 0; i<256; i++)
			Histo[i] = 0;

		//�󵵼� ����
		for(i=0; i<m_size ; i++){
			Histo[m_InputImage[i]]++;
		}

		//����ȭ
		MAX = Histo[0];

		for(i=0; i<256; i++)
		{
			if(Histo[i] > MAX)
				MAX = Histo[i];
		}

		//����ȭ�� ������׷�
		for(i=0; i<256; i++)
			Histo[i] = (int)(Histo[i] * 255 / MAX);
		m_OutputImage = new unsigned char[m_Re_size+(256*20)];

		//������׷� ���
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
		MIN = m_InputImage[0]; // �ּҰ���ã�������ʱⰪ
		MAX = m_InputImage[0]; // �ִ밪��ã�������ʱⰪ
		// �Է¿������ּҰ�ã��
		for(i=0 ; i<m_size; i++){
			if(m_InputImage[i] < MIN)
				MIN = m_InputImage[i];
		}
		// �Է¿������ִ밪ã��
		for(i=0 ; i<m_size; i++){
			if(m_InputImage[i] > MAX)
				MAX = m_InputImage[i];
		}
		m_OutputImage= new unsigned char[m_Re_size];
		// ������׷�stretch
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
		// �ʱ�ȭ
		for (i = 0; i<256; i++)
			m_HIST[i] = LOW;
		// �󵵼�����
		for (i = 0; i<m_size; i++) {
			value = (int)m_InputImage[i];
			m_HIST[value]++;
		}
		// ����������׷�����
		for (i = 0; i<256; i++) {
			SUM += m_HIST[i];
			m_Sum_Of_HIST[i] = SUM;
		}
		m_OutputImage = new unsigned char[m_Re_size];
		// �Է¿�������Ȱȭ�ȿ����������
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
		// OnMaskProcess �Լ���ȣ���Ͽ�ȸ��ó�����Ѵ�.


		/*
		for(i=0 ; i<m_Re_height ; i++){
		for(j=0 ; j<m_Re_width ; j++){
		if(m_tempImage[i][j] > 255.)
		m_tempImage[i][j] = 255.;
		if(m_tempImage[i][j] < 0.)
		m_tempImage[i][j] = 0.;
		}

		} // ȸ��ó�������0~255 ���̰��̵ǵ����Ѵ�.
		*/

		// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
		// ����ȭ�Լ�������Ҷ�
		// ȸ��ó�����������ȭó�������2�����迭���̵ǹǷ�
		// 2�����迭��1�����迭�ιٲپ�����ϵ����Ѵ�.

		for(i=0 ; i<m_Re_height ; i++){
			for(j=0 ; j<m_Re_width ; j++){
				m_OutputImage[i*m_Re_width + j]
				= (unsigned char)(m_tempImage[i][j] + 128);
			}
		}
	}


	double** CPoposhopDoc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
	{
		// ȸ��ó�����Ͼ���Լ�
		int i, j, n, m;
		double **tempInputImage, **tempOutputImage, S = 0.0;
		tempInputImage = Image2DMem(m_height + 2, m_width + 2);
		// �Է°������Ѹ޸��Ҵ�
		tempOutputImage = Image2DMem(m_height, m_width);
		// ��°������Ѹ޸��Ҵ�
		// 1�����Է¿����ǰ���2�����迭���Ҵ��Ѵ�.
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				tempInputImage[i+1][j+1]
				= (double)Target[i * m_width + j];
			}
		}
		// ȸ������
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				for(n=0 ; n<3 ; n++){
					for(m=0 ; m<3 ; m++){
						S += Mask[n][m] * tempInputImage[i+n][j+m];
					}
				} // ȸ������ũ��ũ�⸸ŭ�̵��ϸ鼭��������
				tempOutputImage[i][j] = S; // �����Ȱ�����¸޸𸮿�����
				S = 0.0; // ������������̵��ϸ鴩�������ʱ�ȭ
			}
		}
		return tempOutputImage; // �������ȯ
	}


	double** CPoposhopDoc::OnScale(double **Target, int height, int width)
	{
		// ����ȭ�������Լ�
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
		} // �Ҵ��2�����޸𸮸��ʱ�ȭ
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
		// ����ó��
		// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
		// ����ȭ
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
						// 3*3 ũ��迭��������ũ�迭���Ҵ�
					}
				}
				OnBubleSort(Mask, 9); // ����ũ����ũ�����������
				m_OutputImage[index] = (unsigned char)Mask[4];
				// �߰������
				index++; // ��¹迭����ǥ
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
		//int ZoomRate = 2; // ����Ȯ�����
		double **tempArray;
		if(dlg.DoModal() == IDOK)
		{ 
			m_Re_height = int(dlg.m_SamplingRate * m_height); // Ȯ��ȿ����ǳ���
			m_Re_width = int(dlg.m_SamplingRate * m_width); // Ȯ��ȿ����ǳʺ�
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
					// �̿���ȭ�Ҹ��̿��Ѻ���
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
			m_Re_height = (int)(m_height * dlg.m_SamplingRate); // Ȯ��ȿ����ǳ���
			m_Re_width = (int)(m_width * dlg.m_SamplingRate); // Ȯ��ȿ����ǳʺ�
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
		int i, j, n, m,index = 0; // M = ������ø�����
		//int M = 2;
		CSamplingDig dlg;

		if(dlg.DoModal() == IDOK)
		{ 
			double *Mask, Value;
			Mask = new double [dlg.m_SamplingRate*dlg.m_SamplingRate]; // ����ũ��ũ�����
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
							// �Է¿�������������߶󸶽�ũ�迭������
						}
					}
					OnBubleSort(Mask, dlg.m_SamplingRate*dlg.m_SamplingRate); // ����ũ������Ȱ�������
					Value = Mask[(int)(dlg.m_SamplingRate*dlg.m_SamplingRate/2)]; // ���ĵȰ��߰����������
					m_OutputImage[index] = (unsigned char)Value;
					// ����������
					index++;
				}
			}
		}
	}

	void CPoposhopDoc::OnMeansub(void)
	{
		int i, j, n, m, index = 0, k; // M = ������ø�����
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
					// ����ũ������Ȱ�������
					Value = (Sum / (dlg.m_SamplingRate*dlg.m_SamplingRate)); // ��������
					m_OutputImage[index] = (unsigned char)Value;
					// ��հ������
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
				// �Է¿�����h_pos, w_pos��ŭ�̵�
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
				// �Է� ������ �迭 ���� ��� ������ ����
				// �迭�� ������ ���ڸ����� ����
			}
		}
	}


	void CPoposhopDoc::OnRotation(void)
	{
		int i, j, CenterH, CenterW, newH, newW, degree = 45;
		// degree = ȸ���� ����
		double Radian, PI, **tempArray, Value;
		m_Re_height = m_height; // ȸ���� ������ ����
		m_Re_width = m_width; // ȸ���� ������ �ʺ�
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];
		PI = 3.14159265358979; // ȸ������ ���� PI ��
		Radian = (double)degree*PI / 180.0;
		// degree ���� radian���� ����
		CenterH = m_height / 2; // ������ �߽� ��ǥ
		CenterW = m_width / 2; // ������ �߽� ��ǥ
		m_tempImage = Image2DMem(m_height, m_width);
		tempArray = Image2DMem(m_Re_height, m_Re_width);
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
			}
		}
		for(i=0 ; i<m_height ; i++){
			for(j=0 ; j<m_width ; j++){
				// ȸ�� ��ȯ ����� �̿��Ͽ� ȸ���ϰ� �� ��ǥ �� ���
				newH = (int)((i - CenterH)*cos(Radian) - (j - CenterW)*sin(Radian) + CenterH);
				newW = (int)((i - CenterH)*sin(Radian) + (j - CenterW)*cos(Radian) + CenterW);
				if(newH < 0 || newH >= m_height){
					// ȸ���� ��ǥ�� ��� ������ ���� �迭 ���� �Ѿ ��
					Value = 0;
				}
				else if(newW < 0 || newW >= m_width){
					// ȸ���� ��ǥ�� ��� ������ ���� �迭 ���� �Ѿ ��
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
						// 5*5 ũ�� �迭 ���� ����ũ �迭�� �Ҵ�
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
				// ��� �� ���
				index++; // ��� �迭�� ��ǥ
			}
		}

	}


