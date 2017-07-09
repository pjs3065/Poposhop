#pragma once


// CAvgDlg dialog

class CAvgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAvgDlg)

public:
	CAvgDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAvgDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
