
// MFCTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#include<string>
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCTestApp: 
// �йش����ʵ�֣������ MFCTest.cpp
//

class CMFCTestApp : public CWinApp
{
public:
	CMFCTestApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCTestApp theApp;

