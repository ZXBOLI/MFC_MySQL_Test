#pragma once
#include "afxwin.h"


// Mod 对话框

class Mod : public CDialogEx
{
	DECLARE_DYNAMIC(Mod)

public:
	Mod(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Mod();

// 对话框数据
	enum { IDD = IDD_MOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 组合框
	CComboBox m_Combo1;
	// 姓名
	CString name;
	// 语文成绩
	CString chinese_scr;
	// 数学成绩
	CString math_scr;
	// 英语成绩
	CString english_scr;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedRstButton();
};
