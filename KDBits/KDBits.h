// KDBits.h : KDBits Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CKDBitsApp:
// �йش����ʵ�֣������ KDBits.cpp
//

class CKDBitsApp : public CWinApp
{
public:
	CKDBitsApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CKDBitsApp theApp;