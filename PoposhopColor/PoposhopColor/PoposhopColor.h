
// PoposhopColor.h : PoposhopColor ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPoposhopColorApp:
// �� Ŭ������ ������ ���ؼ��� PoposhopColor.cpp�� �����Ͻʽÿ�.
//

class CPoposhopColorApp : public CWinApp
{
public:
	CPoposhopColorApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPoposhopColorApp theApp;
