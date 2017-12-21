// Del.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Del.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <mysql.h> //mysql���ݿ��Դ���C API�����⣬������亯����libmysql.lib�Ͷ�̬���ӿ�libmysql.dll
#include <string>
#include <cstring>
#include <sstream> //����ת��ר��

#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql���ݿ�Ŀ⺯��

// Del �Ի���

IMPLEMENT_DYNAMIC(Del, CDialogEx)

Del::Del(CWnd* pParent /*=NULL*/)
	: CDialogEx(Del::IDD, pParent)
	, chinese_scr(_T(""))
	, math_scr(_T(""))
	, english_scr(_T(""))
	, name(_T(""))
{

}

Del::~Del()
{
}

void Del::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELID, m_Combo1);
	DDX_Text(pDX, CHI_EDIT, chinese_scr);
	DDX_Text(pDX, MAT_EDIT, math_scr);
	DDX_Text(pDX, ENG_EDIT, english_scr);
	//  DDX_Control(pDX, NAM_EDIT, name);
	DDX_Text(pDX, NAM_EDIT, name);
}


BEGIN_MESSAGE_MAP(Del, CDialogEx)
//	ON_CBN_SELCHANGE(IDC_DELID, &Del::OnSelchangeDelid)
//	ON_CBN_EDITCHANGE(IDC_DELID, &Del::OnEditchangeDelid)
//	ON_CBN_EDITCHANGE(IDC_DELID, &Del::OnEditchangeDelid)
	ON_CBN_SELCHANGE(IDC_DELID, &Del::OnSelchangeDelid)
	ON_BN_CLICKED(DLT_BUTTON, &Del::OnClickedDltButton)
END_MESSAGE_MAP()


// Del ��Ϣ�������




BOOL Del::OnInitDialog()
{
	/*
	ע�����°�Visual C++�У��Ի����OnInitDialog��Ϣ�ѱ��Ϊ�麯��
	�ص㣺����Ҫ��̬����һ����Ͽ����ֵ������Ҫ��дһ���Ի����ʼ���¼��麯��
	*/
	CDialogEx::OnInitDialog();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	const char user[] = "root"; //�������ݿ���û���
	const char pswd[] = "1111"; //����
	const char host[] = "localhost"; //���ݿ��ַ��������������ػ�����
	const char table[] = "students"; //���ݿ���
	unsigned int port = 3306; //�˿ں�
	MYSQL myCont; //���Ӿ��
	MYSQL_RES *result; //��ѯ���
	MYSQL_ROW sql_row; //��ѯ�����У���һά������ʽ��������0��ʼ
	int res; //�Ƿ��ѯ�ɹ�������ֵΪbool����
	mysql_init(&myCont); //��ʼ������
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
		res = mysql_query(&myCont, "select id from score");
		if (!res)
		{
			result = mysql_store_result(&myCont); //�Ƿ񷵻ؽ���������У��򷵻�һά�����ʽ���в�ѯ�������û�У��򷵻ؿ�ָ��
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//ͨ��whileѭ����һ������Ͽ����������
				{
					//�ص㣺�����Ƚ����ݿ��ѯ���ص�char*��תΪCString�Ͳ��ܱ���Ͽ��AddString����ʹ�ã����������
					char *q = sql_row[0];
					CString qid(q);
					m_Combo1.AddString(qid);

				}
			}
		}
		else
		{
			AfxMessageBox(_T("ʧ�ܣ�δ��ѯ��ID"));
		}
	}
	else
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
	}
	//�ͷ���Դ
	mysql_close(&myCont);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Del::OnSelchangeDelid()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*
	�ص㣺����ComboBox�Ŀؼ��¼�CBN_SELCHANGE��������ȡֵ����
	�ؼ������ִ��˳���ִ����ʲô�����⣿

	������CBN_SELCHANGE��Ϣʱ����ʱcombobox�е�����ֵ�ı䣬������ʱ������ֿ����������û�иı䡣
	��ʱGetWindowText()�϶��õ�������ǰ�����ݣ��������Ҫ�ģ������Ժ�����ɹ��������ĸ��£�combobox���������Ҫ�����ݡ�
	��ˣ������θ����⣬�ͱ��������ֵ���֣�
	*/
	int index = ((CComboBox*)GetDlgItem(IDC_DELID))->GetCurSel(); //�����Ҫ������ֵ  
	((CComboBox*)GetDlgItem(IDC_DELID))->SetCurSel(index); //���ó���Ҫ����ֵ��ֵ  
	UpdateData(true);
	CString selid;
	((CComboBox*)GetDlgItem(IDC_DELID))->GetWindowText(selid);
	int len1 = WideCharToMultiByte(CP_ACP, 0, selid, -1, NULL, 0, NULL, NULL);
	char *chr_id = new char[len1 + 1];
	WideCharToMultiByte(CP_ACP, 0, selid, -1, chr_id, len1, NULL, NULL);
	const char user[] = "root"; //�������ݿ���û���
	const char pswd[] = "1111"; //����
	const char host[] = "localhost"; //���ݿ��ַ��������������ػ�����
	const char table[] = "students"; //���ݿ���
	unsigned int port = 3306; //�˿ں�
	char sql1[300]; //�����������sql���
	MYSQL myCont; //���Ӿ��
	MYSQL_RES *result; //��ѯ���
	MYSQL_ROW sql_row; //��ѯ�����У���һά������ʽ��������0��ʼ
	int res; //�Ƿ��ѯ�ɹ�������ֵΪbool����
	mysql_init(&myCont); //��ʼ������
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
		sprintf_s(sql1, "select id, name, Chinese, Math, English from score where id = '%s';", chr_id); //����_s����ȫ
		res = mysql_query(&myCont, sql1);//ʵʩ��ѯ������mysql_query����boolֵ����ѯ�ɹ�Ϊtrue����֮Ϊfalse
		if (!res) //�Ƿ��ѯ�ɹ�
		{
			result = mysql_store_result(&myCont); //�Ƿ񷵻ؽ���������У��򷵻�һά�����ʽ���в�ѯ�������û�У��򷵻ؿ�ָ��
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					name = sql_row[1];
					chinese_scr = sql_row[2];
					math_scr = sql_row[3];
					english_scr = sql_row[4];
				}
			}
			else
			{
				AfxMessageBox(_T("��ѯʧ��"));
			}
		}
	}
	else
	{
		AfxMessageBox(_T("���ݿ�����ʧ��"));
	}
	//�ͷ���Դ
	mysql_close(&myCont);
	UpdateData(FALSE);
}


void Del::OnClickedDltButton() //����ɾ����ť��ִ�С�ɾ������
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (MessageBox(_T("ȷ��ɾ����"), _T("ɾ��"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK) //����һ��ȷ�϶Ի���ȷ���Ƿ�ִ��ɾ��
	{
		/*
		�ص㣺����ComboBox�Ŀؼ��¼�CBN_SELCHANGE��������ȡֵ����
		�ؼ������ִ��˳���ִ����ʲô�����⣿

		������CBN_SELCHANGE��Ϣʱ����ʱcombobox�е�����ֵ�ı䣬������ʱ������ֿ����������û�иı䡣
		��ʱGetWindowText()�϶��õ�������ǰ�����ݣ��������Ҫ�ģ������Ժ�����ɹ��������ĸ��£�combobox���������Ҫ�����ݡ�
		��ˣ������θ����⣬�ͱ��������ֵ����
		*/
		int index = ((CComboBox*)GetDlgItem(IDC_DELID))->GetCurSel(); //�����Ҫ������ֵ  
		((CComboBox*)GetDlgItem(IDC_DELID))->SetCurSel(index); //���ó���Ҫ����ֵ��ֵ  
		UpdateData(true); //����ȡ�������������ı���ֵ
		CString selid;
		((CComboBox*)GetDlgItem(IDC_DELID))->GetWindowText(selid);
		//CStringתchar*���Ա��ڷ���sql�����
		int len1 = WideCharToMultiByte(CP_ACP, 0, selid, -1, NULL, 0, NULL, NULL);
		char *chr_id = new char[len1 + 1];
		WideCharToMultiByte(CP_ACP, 0, selid, -1, chr_id, len1, NULL, NULL);
		const char user[] = "root"; //�������ݿ���û���
		const char pswd[] = "1111"; //����
		const char host[] = "localhost"; //���ݿ��ַ��������������ػ�����
		const char table[] = "students"; //���ݿ���
		unsigned int port = 3306; //�˿ں�
		char sql2[300]; //�����������sql���
		MYSQL myCont; //���Ӿ��
		MYSQL_RES *result; //��ѯ���
		MYSQL_ROW sql_row; //��ѯ�����У���һά������ʽ��������0��ʼ
		int res; //�Ƿ��ѯ�ɹ�������ֵΪbool����
		mysql_init(&myCont); //��ʼ������
		if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
		{
			mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
			sprintf_s(sql2, "delete from score where id = '%s';", chr_id); //ɾ������
			res = mysql_query(&myCont, sql2);//ʵʩ��ɾ������������mysql_query����boolֵ��ɾ���ɹ�Ϊtrue����֮Ϊfalse
			if (res == 0)
			{
				AfxMessageBox(_T("ɾ���ɹ�"));
				CDialogEx::OnOK(); //���Ի�������OK״̬���˳�
			}
			else
			{
				AfxMessageBox(_T("ɾ��ʧ��"));
			}
		}
		else
		{
			AfxMessageBox(_T("���ݿ�����ʧ��"));
		}
		//�ͷ���Դ
		mysql_close(&myCont);
		UpdateData(FALSE);
	}
	else
	{
		return; //����ָ����ȷ��ɾ�������ĶԻ���������ȡ�����򷵻�
	}
}
