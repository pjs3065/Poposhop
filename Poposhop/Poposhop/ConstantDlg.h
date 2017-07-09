#pragma once


// CConstantDlg dialog

class CConstantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConstantDlg)

public:
	CConstantDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConstantDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
