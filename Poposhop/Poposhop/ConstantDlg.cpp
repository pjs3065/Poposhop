// ConstantDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Poposhop.h"
#include "ConstantDlg.h"
#include "afxdialogex.h"


// CConstantDlg dialog

IMPLEMENT_DYNAMIC(CConstantDlg, CDialogEx)

CConstantDlg::CConstantDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConstantDlg::IDD, pParent)
	, m_Constant(0)
{

}

CConstantDlg::~CConstantDlg()
{
}

void CConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Constant);
	DDV_MinMaxDouble(pDX, m_Constant, 0, 255);
}


BEGIN_MESSAGE_MAP(CConstantDlg, CDialogEx)
END_MESSAGE_MAP()


// CConstantDlg message handlers
