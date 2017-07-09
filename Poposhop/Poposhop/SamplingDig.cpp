// SamplingDig.cpp : implementation file
//

#include "stdafx.h"
#include "Poposhop.h"
#include "SamplingDig.h"
#include "afxdialogex.h"


// CSamplingDig dialog

IMPLEMENT_DYNAMIC(CSamplingDig, CDialogEx)

CSamplingDig::CSamplingDig(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSamplingDig::IDD, pParent)
	, m_SamplingRate(0)
{

}

CSamplingDig::~CSamplingDig()
{
}

void CSamplingDig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SamplingRate);
	DDV_MinMaxInt(pDX, m_SamplingRate, 1, 32);
}


BEGIN_MESSAGE_MAP(CSamplingDig, CDialogEx)
END_MESSAGE_MAP()


// CSamplingDig message handlers
