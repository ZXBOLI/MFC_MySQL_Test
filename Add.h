#pragma once


// Add �Ի���

class Add : public CDialogEx
{
	DECLARE_DYNAMIC(Add)

public:
	Add(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Add();

// �Ի�������
	enum { IDD = IDD_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ӵ�����
	CString name;
	// ��ӵ���ѧ�ɼ�
	CString math_scr;
	// ��ӵ����ĳɼ�
	CString chinese_scr;
	// ��ӵ�Ӣ��ɼ�
	CString english_scr;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedRstButton();
};
