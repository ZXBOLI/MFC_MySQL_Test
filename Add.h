#pragma once


// Add 对话框

class Add : public CDialogEx
{
	DECLARE_DYNAMIC(Add)

public:
	Add(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Add();

// 对话框数据
	enum { IDD = IDD_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 添加的姓名
	CString name;
	// 添加的数学成绩
	CString math_scr;
	// 添加的语文成绩
	CString chinese_scr;
	// 添加的英语成绩
	CString english_scr;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedRstButton();
};
