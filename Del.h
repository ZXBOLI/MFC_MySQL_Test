#pragma once
#include "afxwin.h"


// Del �Ի���

class Del : public CDialogEx
{
	DECLARE_DYNAMIC(Del)

public:
	Del(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Del();

// �Ի�������
	enum { IDD = IDD_DEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��Ͽ�
	CComboBox m_Combo1;
	// ���ĳɼ�
	CString chinese_scr;
	// ��ѧ�ɼ�
	CString math_scr;
	// Ӣ��ɼ�
	CString english_scr;
	// ����	// ����
	CString name;
	virtual BOOL OnInitDialog();
//	afx_msg void OnSelchangeDelid();
//	afx_msg void OnEditchangeDelid();
//	afx_msg void OnEditchangeDelid();
	afx_msg void OnSelchangeDelid();
	afx_msg void OnClickedDltButton();
};
