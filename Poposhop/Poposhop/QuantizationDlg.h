#pragma once


// CQuantizationDlg dialog

class CQuantizationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQuantizationDlg)

public:
	CQuantizationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CQuantizationDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_QuantBit;
};
