// QuantizationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poposhop.h"
#include "QuantizationDlg.h"
#include "afxdialogex.h"


// CQuantizationDlg dialog

IMPLEMENT_DYNAMIC(CQuantizationDlg, CDialogEx)

CQuantizationDlg::CQuantizationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQuantizationDlg::IDD, pParent)
	, m_QuantBit(0)
{

}

CQuantizationDlg::~CQuantizationDlg()
{
}

void CQuantizationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_QuantBit);
	DDV_MinMaxDouble(pDX, m_QuantBit, 1, 8);
}


BEGIN_MESSAGE_MAP(CQuantizationDlg, CDialogEx)
END_MESSAGE_MAP()


// CQuantizationDlg message handlers
