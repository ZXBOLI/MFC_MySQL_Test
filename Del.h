#pragma once
#include "afxwin.h"


// Del 对话框

class Del : public CDialogEx
{
	DECLARE_DYNAMIC(Del)

public:
	Del(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Del();

// 对话框数据
	enum { IDD = IDD_DEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 组合框
	CComboBox m_Combo1;
	// 语文成绩
	CString chinese_scr;
	// 数学成绩
	CString math_scr;
	// 英语成绩
	CString english_scr;
	// 姓名	// 姓名
	CString name;
	virtual BOOL OnInitDialog();
//	afx_msg void OnSelchangeDelid();
//	afx_msg void OnEditchangeDelid();
//	afx_msg void OnEditchangeDelid();
	afx_msg void OnSelchangeDelid();
	afx_msg void OnClickedDltButton();
};
