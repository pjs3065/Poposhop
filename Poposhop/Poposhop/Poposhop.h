
// Poposhop.h : Poposhop ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPoposhopApp:
// �� Ŭ������ ������ ���ؼ��� Poposhop.cpp�� �����Ͻʽÿ�.
//

class CPoposhopApp : public CWinApp
{
public:
	CPoposhopApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPoposhopApp theApp;
