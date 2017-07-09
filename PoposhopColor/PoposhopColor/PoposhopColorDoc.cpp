
// PoposhopColorDoc.cpp : CPoposhopColorDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PoposhopColor.h"
#include <math.h>
#endif

#include "PoposhopColorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPoposhopColorDoc

IMPLEMENT_DYNCREATE(CPoposhopColorDoc, CDocument)

	BEGIN_MESSAGE_MAP(CPoposhopColorDoc, CDocument)
	END_MESSAGE_MAP()


	// CPoposhopColorDoc 생성/소멸

	CPoposhopColorDoc::CPoposhopColorDoc()
	{
		// TODO: 여기에 일회성 생성 코드를 추가합니다.

	}

	CPoposhopColorDoc::~CPoposhopColorDoc()
	{
	}

	BOOL CPoposhopColorDoc::OnNewDocument()
	{
		if (!CDocument::OnNewDocument())
			return FALSE;

		// TODO: 여기에 재초기화 코드를 추가합니다.
		// SDI 문서는 이 문서를 다시 사용합니다.

		return TRUE;
	}




	// CPoposhopColorDoc serialization

	void CPoposhopColorDoc::Serialize(CArchive& ar)
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
	void CPoposhopColorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
	void CPoposhopColorDoc::InitializeSearchContent()
	{
		CString strSearchContent;
		// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
		// 콘텐츠 부분은 ";"로 구분되어야 합니다.

		// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
		SetSearchContent(strSearchContent);
	}

	void CPoposhopColorDoc::SetSearchContent(const CString& value)
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

	// CPoposhopColorDoc 진단

#ifdef _DEBUG
	void CPoposhopColorDoc::AssertValid() const
	{
		CDocument::AssertValid();
	}

	void CPoposhopColorDoc::Dump(CDumpContext& dc) const
	{
		CDocument::Dump(dc);
	}
#endif //_DEBUG


	// CPoposhopColorDoc 명령


	BOOL CPoposhopColorDoc::OnOpenDocument(LPCTSTR lpszPathName)
	{
		if (!CDocument::OnOpenDocument(lpszPathName))
			return FALSE;

		CFile File;

		File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

		if (File.GetLength() == 256 * 256 * 3)
		{
			m_height = 256;
			m_width = 256;
		}

		m_size = m_width * m_height;

		if (File.GetLength() == m_width * m_height * 3)
		{
			//AfxMessageBox(_T("come in"));
			File.Read(m_OpenImg, m_width * m_height * 3);
			File.Close();
			//AfxMessageBox(_T("come out"));
		}
		return TRUE;
	}


	void CPoposhopColorDoc::OnToHsi(void)
	{
		int y, x;

		for (y = 0; y < 255; y++)
		{
			for (x = 0; x < 255; x++)
			{
				m_ResultImg[y][x][0] = Sol_H(m_OpenImg[y][x][0], m_OpenImg[y][x][1], m_OpenImg[y][x][2]);
				m_HSI[y][x][0] = m_ResultImg[y][x][0];
				m_ResultImg[y][x][1] = Sol_S(m_OpenImg[y][x][0], m_OpenImg[y][x][1], m_OpenImg[y][x][2]);
				m_HSI[y][x][1] = m_ResultImg[y][x][1];
				m_ResultImg[y][x][2] = Sol_I(m_OpenImg[y][x][0], m_OpenImg[y][x][1], m_OpenImg[y][x][2]);
				m_HSI[y][x][2] = m_ResultImg[y][x][2];
			}
		}



	}


	unsigned char CPoposhopColorDoc::Sol_H(unsigned char R, unsigned char G, unsigned char B)
	{
		double angle;
		double RR, GG, BB;

		if (R == G && G == B)
			return 0;

		RR = R / 255.0;
		GG = G / 255.0;
		BB = B / 255.0;

		angle = (RR - 0.5*GG - 0.5*BB) / (float)sqrt((RR - GG)*(RR - GG) + (RR - BB)*(GG - BB));
		angle = acos(angle);
		angle *= 57.29577951;

		if (B > G)
			angle = 360.0 - angle;

		return (unsigned char)((angle / 360.0)*255.0);
	}


	unsigned char CPoposhopColorDoc::Sol_S(unsigned char R, unsigned char G, unsigned char B)
	{
		double minc;
		double RR, GG, BB;

		RR = R / 255.0;
		GG = G / 255.0;
		BB = B / 255.0;

		if (RR + GG + BB == 0)
			return 0;

		minc = Min(RR, GG);
		minc = Min(minc, BB);

		return (unsigned char)((1.0 - (3.0 / (RR + GG + BB))*minc)*255.0);
	}


	unsigned char CPoposhopColorDoc::Sol_I(unsigned char R, unsigned char G, unsigned char B)
	{
		double RR, GG, BB;

		RR = R / 255.0;
		GG = G / 255.0;
		BB = B / 255.0;

		return (unsigned char)(((RR + GG + BB) / 3) * 255.0);
	}

	double CPoposhopColorDoc::Min(double a, double b)
	{
		if (a <= b)
			return a;
		else
			return b;
	}


	void CPoposhopColorDoc::OnToRgb(void)
	{
		double H, S, I;
		double RR, GG, BB;
		double angle1, angle2;

		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j < 256; j++)
			{
				H = (double)((m_HSI[i][j][0] / 255.0) * 360.0);
				S = (double)((m_HSI[i][j][1] / 255.0));
				I = (double)((m_HSI[i][j][2] / 255.0));

				if (I <= 0.0)
				{
					m_ResultImg[i][j][0] = 0;
					m_ResultImg[i][j][1] = 0;
					m_ResultImg[i][j][2] = 0;
					continue;
				}

				if (I >= 1.0)
				{
					m_ResultImg[i][j][0] = 255;
					m_ResultImg[i][j][1] = 255;
					m_ResultImg[i][j][2] = 255;
					continue;
				}

				if (H < 0.0)
					H += 360;
				if (H <= 120.0)
				{
					angle1 = H * 0.017453293;
					angle2 = (60 - H)*0.0177453293;
					BB = (1.0 - S) / 3.0;
					RR = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
					GG = 1.0 - RR - BB;
				}
				else if (120.0 < H && H <= 240.0)
				{
					H = H - 120.0;
					angle1 = H * 0.017453293;
					angle2 = (60 - H)*0.0177453293;
					RR = (1.0 - S) / 3.0;
					GG = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
					BB = 1.0 - RR - GG;
				}
				else
				{
					H = H - 240.0;
					angle1 = H * 0.017453293;
					angle2 = (60 - H)*0.0177453293;
					GG = (1.0 - S) / 3.0;
					BB = (1.0 + (S*cos(angle1) / cos(angle2))) / 3.0;
					RR = 1.0 - GG - BB;
				}

				RR = RR*255.0 * 3.0 * I;
				GG = GG*255.0 * 3.0 * I;
				BB = BB*255.0 * 3.0 * I;

				if (RR > 255.0)
					RR = 255.0;
				if (GG > 255.0)
					GG = 255.0;
				if (BB > 255.0)
					BB = 255.0;
				m_ResultImg[i][j][0] = unsigned char(RR);
				m_ResultImg[i][j][1] = unsigned char(GG);
				m_ResultImg[i][j][2] = unsigned char(BB);
			}
		}
	}


	void CPoposhopColorDoc::OnMenuLightcompensation(void)
	{
		double Y[255][255];
		double minY = 9999999.0;
		double maxY = -0000000.0;

		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{
				Y[i][j] = 0.299 * m_OpenImg[i][j][0] + 0.587*m_OpenImg[i][j][1] + 0.114*m_OpenImg[i][j][2];
			}
		}

		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{
				if (Y[i][j] > maxY) maxY = Y[i][j];
				if (Y[i][j] < minY) minY = Y[i][j];
			}
		}

		double Yr = maxY - (maxY - minY) * 0.05;
		int Yr_count = 0;

		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{
				if (Y[i][j] > Yr) Yr_count++;
			}
		}

		double Rave, Gave, Bave;
		Rave = Gave = Bave = 0.0;

		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{
				if (Y[i][j] > Yr)
				{
					Rave += (double)m_OpenImg[i][j][0] / Yr_count;
					Gave += (double)m_OpenImg[i][j][1] / Yr_count;
					Bave += (double)m_OpenImg[i][j][2] / Yr_count;
				}
			}
		}

		double Rratio = 255.0 / Rave;
		double Gratio = 255.0 / Gave;
		double Bratio = 255.0 / Bave;

		double R, G, B;

		for (int i = 0; i < 255; i++)
		{
			for (int j = 0; j < 255; j++)
			{

				R = m_OpenImg[i][j][0] * Rratio;
				G = m_OpenImg[i][j][1] * Gratio;
				B = m_OpenImg[i][j][2] * Bratio;
				if (R >= 255.0) R = 255.0;
				if (G >= 255.0) G = 255.0;
				if (B >= 255.0) B = 255.0;
				m_ResultImg[i][j][0] = (unsigned char)R;
				m_ResultImg[i][j][1] = (unsigned char)G;
				m_ResultImg[i][j][2] = (unsigned char)B;
			}
		}
	}


	void CPoposhopColorDoc::OnMenuKMeans(void)
	{
		static const int K = 8;
		int loop = 1, first = 1;
		int cluster[256][256] = { K + 1, };
		int preCluster;
		double sum[K][3];
		double center[K][3] = { 0.0, }, pre_center[K][3] = { -1.0, };
		double min = 9999999999.9;
		int minIndex;
		int number[K];
		double dist;

		for (int k = 0; k < K; k++) {
			int x, y;
			x = rand() % 256;
			y = rand() % 256;
			center[k][0] = (double)m_OpenImg[x][y][0];
			center[k][1] = (double)m_OpenImg[x][y][1];
			center[k][2] = (double)m_OpenImg[x][y][2];
		}

		while (loop == 1) 
		{
			loop = 0;
			for (int i = 0; i < 256; i++) 
			{
				for (int j = 0; j < 256; j++) 
				{
					preCluster = cluster[i][j];
					min = 99999999.9;
					//minIndex = -1;
					for (int k = 0; k < K; k++) 
					{
						//if (first == 1 || ((pre_center[k][0] != center[k][0]) || (pre_center[k][1] != center[k][1]) || (pre_center[k][2] != center[k][2])))
						//{
						dist =
							sqrt(pow(m_OpenImg[i][j][0] - center[k][0], 2.0) +
							pow(m_OpenImg[i][j][1] - center[k][1], 2.0) +
							pow(m_OpenImg[i][j][2] - center[k][2], 2.0));
						if (dist < min)
						{
							min = dist;
							minIndex = k;
						}
						//}
					}
					//if (minIndex != -1)
					//{
					cluster[i][j] = minIndex;
					//}

					if (cluster[i][j] != preCluster)		
						loop = 1;		
				}

				for (int k = 0; k < K; k++) 
				{		
					sum[k][0] = 0.0; sum[k][1] = 0.0; sum[k][2] = 0.0;		
					number[k] = 0;
				}

				for (int i = 0; i < 256; i++) 
				{
					for (int j = 0; j < 256; j++) 
					{
						sum[cluster[i][j]][0] += m_OpenImg[i][j][0];
						sum[cluster[i][j]][1] += m_OpenImg[i][j][1];
						sum[cluster[i][j]][2] += m_OpenImg[i][j][2];
						number[cluster[i][j]]++;	
					}	
				}
				for (int k = 0; k < K; k++) 
				{
					pre_center[k][0] = center[k][0];
					pre_center[k][1] = center[k][1];
					pre_center[k][2] = center[k][2];
					center[k][0] = sum[k][0] / number[k];
					center[k][1] = sum[k][1] / number[k];
					center[k][2] = sum[k][2] / number[k];
					//if (first == 1)
					//first = 0;
				}		
			}

			for (int i = 0; i < 256; i++)
			{
				for (int j = 0; j < 256; j++)
				{
					m_ResultImg[i][j][0] = (unsigned char)center[cluster[i][j]][0];
					m_ResultImg[i][j][1] = (unsigned char)center[cluster[i][j]][1];
					m_ResultImg[i][j][2] = (unsigned char)center[cluster[i][j]][2];
				}
			}	
		}
	}

	void CPoposhopColorDoc::OnMenuEqualization(void)
	{
		int i;
		unsigned char Temp, value;
		double m_Hist[256] = { 0.0, }, m_Hist_Sum[256], SUM = 0.0;

		OnToHsi(); // InputImage(RGB)를 HSI형식으로 변환후 m_HSI[256][256][3] 에 저장한다.

		m_Re_height = 256;
		m_Re_width = 256;
		m_Re_size = m_Re_height * m_Re_width;

		for (int y = 0; y < m_Re_height; y++)
		{
			for (int x = 0; x < m_Re_width; x++)
			{
				value = m_HSI[y][x][2];
				m_Hist[value]++;
			}
		} // 빈도수 조사

		for (i = 0; i < 256; i++)
		{
			SUM += m_Hist[i];
			m_Hist_Sum[i] = SUM;
		} // 증가값 히스토그램 생성

		for (int y = 0; y < m_Re_height; y++)
		{
			for (int x = 0; x < m_Re_width; x++)
			{
				Temp = m_HSI[y][x][2];
				m_HSI[y][x][2] = (unsigned char)(m_Hist_Sum[Temp] * 255 / SUM);
			}
		} // 결과값 변경

		haveColor = 1;
		OnToRgb();  // 변경된 결과값 RGB형태로 변경.
		transform = 1;
	}

	void CPoposhopColorDoc::OnMenuKuwahara(void)
	{
		int i, j, n, m;
		unsigned char temp_HSI[256][256] = { 0, };
		kwu A, B, C, D;

		OnToHsi(); // InputImage(RGB)를 HSI형식으로 변환후 m_HSI[256][256][3] 에 저장한다.

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		for (i = 0; i < m_height; i++)
		{
			for (j = 0; j < m_width; j++)
			{
				if (isValid(j - 3, i - 3, m_Re_width, m_Re_height))  // A part
				{
					for (n = 0; n < 3; n++)
					{
						for (m = 0; m < 3; m++)
						{
							A.Mask[n * 3 + m] = m_OpenImg[(i - 3) + n][(j - 3) + m][2];
						}
					} // 9개의 화소값 Insert 완료.
					A.setAvg();
					A.setDist();
				}

				if (isValid(j, i - 3, m_Re_width, m_Re_height))  // B part
				{
					for (n = 0; n < 3; n++)
					{
						for (m = 0; m < 3; m++)
						{
							B.Mask[n * 3 + m] = m_OpenImg[(i - 3) + n][j + m][2];
						}
					} // 9개의 화소값 Insert 완료.
					B.setAvg();
					B.setDist();
				}

				if (isValid(j - 3, i, m_Re_width, m_Re_height))  // C part
				{
					for (n = 0; n < 3; n++)
					{
						for (m = 0; m < 3; m++)
						{
							C.Mask[n * 3 + m] = m_OpenImg[i + n][(j - 3) + m][2];
						}
					} // 9개의 화소값 Insert 완료.
					C.setAvg();
					C.setDist();
				}

				if (isValid(j, i, m_Re_width, m_Re_height))  // D part
				{
					for (n = 0; n < 3; n++)
					{
						for (m = 0; m < 3; m++)
						{
							D.Mask[n * 3 + m] = m_OpenImg[i + n][j + m][2];
						}
					} // 9개의 화소값 Insert 완료.
					D.setAvg();
					D.setDist();
				}
				temp_HSI[i][j] = (unsigned char)getMin(A, B, C, D).Avg;
				init(A, B, C, D);
			}
		}
		for (i = 0; i < m_height; i++)
		{
			for (j = 0; j < m_width; j++)
			{
				m_HSI[i][j][2] = temp_HSI[i][j];
			}
		}
		haveColor = 1;
		OnToRgb();  // 변경된 결과값 RGB형태로 변경.
		transform = 1;
	}

	bool CPoposhopColorDoc::isValid(int x, int y, int width, int height)
	{
		if (x >= 0 && x + 3 < width && y >= 0 && y + 3 < height)
			return true;
		else
			return false;
	}

	double** CPoposhopColorDoc::Image2DMem(int height, int width)
	{
		// 2차원 메모리 할당을 위한 함수
		double** temp;
		int i, j;
		temp = new double *[height];
		for (i = 0; i < height; i++) {
			temp[i] = new double[width];
		}
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				temp[i][j] = 0.0;
			}
		} // 할당된 2차원 메모리를 초기화
		return temp;
	}

	double CPoposhopColorDoc::getAvg(double mask[], int length)
	{
		double total = 0;
		for (int i = 0; i < length; i++)
			total += mask[i];
		return (total / length);
	}

	double CPoposhopColorDoc::getVariance(double mask[], int length)
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

	double* CPoposhopColorDoc::OnDivideMask(double g[], int length, int start)
	{
		double *Sub = new double[9];
		int subIndex = 0;
		for (int j = 0; j < 3; j++) {
			for (int i = (start + (j * 5)); i < (start + (j * 5)) + 3; i++)
			{
				Sub[subIndex] = g[i];
				subIndex++;
			}
			if (subIndex == 9)
				break;
		}
		return Sub;

	}

kwu CPoposhopColorDoc::getMin(kwu A, kwu B, kwu C, kwu D)
{
	kwu list[4] = { A,B,C,D };
	int flag[4] = { 1,1,1,1 };
	for (int i = 0; i < 4; i++)
	{
		if (list[i].Dist == -1.0)  // 특정 point에서 해당 영역(A or B or C or D)은 valid한 상태가 아니므로, Avg , Dist 값이 정해지지 않았다.
			flag[i] = 0;
	}

	double min_dist = 10000000;
	int min_index = 0;

	for (int i = 0; i < 4; i++)
	{
		if (flag[i] == 1)
		{
			if (min_dist > list[i].Dist)
			{
				min_dist = list[i].Dist;
				min_index = i;
			}
		}
	}
	return list[min_index];
}

void CPoposhopColorDoc::init(kwu A, kwu B, kwu C, kwu D)
{
	kwu list[4] = { A,B,C,D };
	for (int i = 0; i < 4; i++)
	{
		list[i].Avg = -1.0;
		list[i].Dist = -1.0;
	}
}

