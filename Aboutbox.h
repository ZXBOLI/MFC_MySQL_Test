#pragma once


// Aboutbox 对话框

class Aboutbox : public CDialogEx
{
	DECLARE_DYNAMIC(Aboutbox)

public:
	Aboutbox(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Aboutbox();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
