#pragma once
#include "afxwin.h"


// Mod �Ի���

class Mod : public CDialogEx
{
	DECLARE_DYNAMIC(Mod)

public:
	Mod(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Mod();

// �Ի�������
	enum { IDD = IDD_MOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��Ͽ�
	CComboBox m_Combo1;
	// ����
	CString name;
	// ���ĳɼ�
	CString chinese_scr;
	// ��ѧ�ɼ�
	CString math_scr;
	// Ӣ��ɼ�
	CString english_scr;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedRstButton();
};
