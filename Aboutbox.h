#pragma once


// Aboutbox �Ի���

class Aboutbox : public CDialogEx
{
	DECLARE_DYNAMIC(Aboutbox)

public:
	Aboutbox(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Aboutbox();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
