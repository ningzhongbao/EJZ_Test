
// EJZ_Test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEJZ_TestApp: 
// �йش����ʵ�֣������ EJZ_Test.cpp
//

class CEJZ_TestApp : public CWinApp
{
public:
	CEJZ_TestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEJZ_TestApp theApp;