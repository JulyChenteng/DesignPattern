
// ThreadSync.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CThreadSyncApp: 
// �йش����ʵ�֣������ ThreadSync.cpp
//

class CThreadSyncApp : public CWinApp
{
public:
	CThreadSyncApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CThreadSyncApp theApp;