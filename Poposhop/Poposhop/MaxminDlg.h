#pragma once


// CMaxminDlg dialog

class CMaxminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMaxminDlg)

public:
	CMaxminDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMaxminDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
