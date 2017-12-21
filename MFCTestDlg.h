
// MFCTestDlg.h : 头文件
//

#pragma once


// CMFCTestDlg 对话框
class CMFCTestDlg : public CDialogEx
{
// 构造
public:
	CMFCTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 学号
	int number;
	// 姓名
	CString name;
	// 语文成绩
	int chinese_scr;
	// 数学成绩
	int math_scr;
	// 英语成绩
	int english_scr;
	// 平均分
	int average;
	// 总分
	int total;
	// 要被查找的学号
//	int search;
	afx_msg void OnQryButton();
	// 待查找学号
	CString search;
	afx_msg void OnClickedAbout();
	afx_msg void OnClickedAddButton();
	afx_msg void OnClickedDelButton();
	afx_msg void OnClickedModButton();
};
