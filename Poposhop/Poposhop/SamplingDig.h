#pragma once


// CSamplingDig dialog

class CSamplingDig : public CDialogEx
{
	DECLARE_DYNAMIC(CSamplingDig)

public:
	CSamplingDig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSamplingDig();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_SamplingRate;
};
