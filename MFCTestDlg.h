
// MFCTestDlg.h : ͷ�ļ�
//

#pragma once


// CMFCTestDlg �Ի���
class CMFCTestDlg : public CDialogEx
{
// ����
public:
	CMFCTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ѧ��
	int number;
	// ����
	CString name;
	// ���ĳɼ�
	int chinese_scr;
	// ��ѧ�ɼ�
	int math_scr;
	// Ӣ��ɼ�
	int english_scr;
	// ƽ����
	int average;
	// �ܷ�
	int total;
	// Ҫ�����ҵ�ѧ��
//	int search;
	afx_msg void OnQryButton();
	// ������ѧ��
	CString search;
	afx_msg void OnClickedAbout();
	afx_msg void OnClickedAddButton();
	afx_msg void OnClickedDelButton();
	afx_msg void OnClickedModButton();
};
