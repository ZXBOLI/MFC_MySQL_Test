// Aboutbox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Aboutbox.h"
#include "afxdialogex.h"


// Aboutbox �Ի���

IMPLEMENT_DYNAMIC(Aboutbox, CDialogEx)

Aboutbox::Aboutbox(CWnd* pParent /*=NULL*/)
	: CDialogEx(Aboutbox::IDD, pParent)
{

}

Aboutbox::~Aboutbox()
{
}

void Aboutbox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Aboutbox, CDialogEx)
END_MESSAGE_MAP()


// Aboutbox ��Ϣ�������
