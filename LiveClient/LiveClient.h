
// LiveClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������




// CLiveClientApp: 
// �йش����ʵ�֣������ LiveClient.cpp
//

class CLiveClientApp : public CWinApp
{
public:
	CLiveClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLiveClientApp theApp;