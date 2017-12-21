// Mod.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Mod.h"
#include "afxdialogex.h"
#include <mysql.h> //mysql���ݿ��Դ���C API�����⣬������亯����libmysql.lib�Ͷ�̬���ӿ�libmysql.dll
#include <string>
#include <cstring>
#include <sstream> //����ת��ר��

#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql���ݿ�Ŀ⺯��


// Mod �Ի���

IMPLEMENT_DYNAMIC(Mod, CDialogEx)

Mod::Mod(CWnd* pParent /*=NULL*/)
	: CDialogEx(Mod::IDD, pParent)
	, name(_T(""))
	, chinese_scr(_T(""))
	, math_scr(_T(""))
	, english_scr(_T(""))
{

}

Mod::~Mod()
{
}

void Mod::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_COMBO, m_Combo1);
	DDX_Text(pDX, NAM_EDIT, name);
	DDX_Text(pDX, CHN_EDIT, chinese_scr);
	DDX_Text(pDX, MAT_EDIT, math_scr);
	DDX_Text(pDX, ENG_EDIT, english_scr);
}


BEGIN_MESSAGE_MAP(Mod, CDialogEx)
	ON_CBN_SELCHANGE(ID_COMBO, &Mod::OnSelchangeCombo)
	ON_BN_CLICKED(IDOK, &Mod::OnBnClickedOk)
	ON_BN_CLICKED(RST_BUTTON, &Mod::OnClickedRstButton)
END_MESSAGE_MAP()


// Mod ��Ϣ�������


BOOL Mod::OnInitDialog() //��ʼ���Ի������¼�
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*
	ע�����°�Visual C++�У��Ի����OnInitDialog��Ϣ�ѱ��Ϊ�麯��
	�ص㣺����Ҫ��̬����һ����Ͽ����ֵ������Ҫ��дһ���Ի����ʼ���¼��麯��
	*/
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


void Mod::OnSelchangeCombo() //����Ͽ�ѡ��仯ʱ
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*
	�ص㣺����ComboBox�Ŀؼ��¼�CBN_SELCHANGE��������ȡֵ����
	�ؼ������ִ��˳���ִ����ʲô�����⣿

	������CBN_SELCHANGE��Ϣʱ����ʱcombobox�е�����ֵ�ı䣬������ʱ������ֿ����������û�иı䡣
	��ʱGetWindowText()�϶��õ�������ǰ�����ݣ��������Ҫ�ģ������Ժ�����ɹ��������ĸ��£�combobox���������Ҫ�����ݡ�
	��ˣ������θ����⣬�ͱ��������ֵ����
	*/
	int index = ((CComboBox*)GetDlgItem(ID_COMBO))->GetCurSel(); //�����Ҫ������ֵ  
	((CComboBox*)GetDlgItem(ID_COMBO))->SetCurSel(index); //���ó���Ҫ����ֵ��ֵ  
	UpdateData(true);
	CString selid;
	((CComboBox*)GetDlgItem(ID_COMBO))->GetWindowText(selid);
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


void Mod::OnBnClickedOk() //��ȷ����ť�����º�ִ�С��ġ�����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
		int index = ((CComboBox*)GetDlgItem(ID_COMBO))->GetCurSel(); //�����Ҫ������ֵ  
		((CComboBox*)GetDlgItem(ID_COMBO))->SetCurSel(index); //���ó���Ҫ����ֵ��ֵ  
		UpdateData(true);
		CString selid;
		((CComboBox*)GetDlgItem(ID_COMBO))->GetWindowText(selid);
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
		CString local_chinese;
		CString local_math;
		CString local_english;
		//��ÿ���ı�����ȡ��ֵ�����������ֶ���CString��תΪchar*�ͣ��Ա��ڲ�����sql��䣬����ʱname�����޸�
		GetDlgItemText(CHN_EDIT, local_chinese);
		GetDlgItemText(MAT_EDIT, local_math);
		GetDlgItemText(ENG_EDIT, local_english);
		int len5 = WideCharToMultiByte(CP_ACP, 0, local_chinese, -1, NULL, 0, NULL, NULL);
		int len6 = WideCharToMultiByte(CP_ACP, 0, local_math, -1, NULL, 0, NULL, NULL);
		int len7 = WideCharToMultiByte(CP_ACP, 0, local_english, -1, NULL, 0, NULL, NULL);
		char *chr_chn = new char[len5 + 1];
		char *chr_mat = new char[len6 + 1];
		char *chr_eng = new char[len7 + 1];
		WideCharToMultiByte(CP_ACP, 0, local_chinese, -1, chr_chn, len5, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, local_math, -1, chr_mat, len6, NULL, NULL);
		WideCharToMultiByte(CP_ACP, 0, local_english, -1, chr_eng, len7, NULL, NULL);
		//���ɼ���CString��תΪint�ͣ��Ա��ں��������ֵȡֵ�߽����
		int i_chi;
		int i_mat;
		int i_eng;
		swscanf_s(local_chinese, _T("%d"), &i_chi);
		swscanf_s(local_math, _T("%d"), &i_mat);
		swscanf_s(local_english, _T("%d"), &i_eng);
		mysql_init(&myCont); //��ʼ������
		if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
		{
			if (!(i_chi > 100 || i_mat > 100 || i_eng > 100)) //��ֵȡֵ�߽�������������ܴ���100����Ϊ������Դ��ͼ�н������ı����number������Ϊtrue�����Բ����ܻ����븺�ţ���˲��ü��ֵΪ�������
			{
				mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
				sprintf_s(sql2, "update score set Chinese ='%s',Math ='%s',English ='%s' where id = '%s';", chr_chn, chr_mat, chr_eng, chr_id); //��ת������ֶμ���sql�����
				res = mysql_query(&myCont, sql2);//ʵʩ���ġ�����������mysql_query����boolֵ���޸ĳɹ�Ϊtrue����֮Ϊfalse
				if (res == 0)
				{
					AfxMessageBox(_T("���³ɹ�"));
					CDialogEx::OnOK();
					//CStringתchar*�Ĺ���������new�����ڴ�ռ䣬��������Ҫ��delete���
					delete[] chr_chn;
					delete[] chr_mat;
					delete[] chr_eng;
				}
				else
				{
					AfxMessageBox(_T("����ʧ��"));
					//��ʹ����ʧ��Ҳ��Ҫ����ڴ�
					delete[] chr_chn;
					delete[] chr_mat;
					delete[] chr_eng;
				}
			}
			else
			{
				AfxMessageBox(_T("���ݲ��ڷ�Χ��\n������Χ��0��100"));
				//��ʹ�������ݲ��Ϸ�Ҳ��Ҫ����ڴ�
				delete[] chr_chn;
				delete[] chr_mat;
				delete[] chr_eng;
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

void Mod::OnClickedRstButton() //�������ð�ť��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ָ�뷨��տؼ���ֵ
	GetDlgItem(CHN_EDIT)->SetWindowText(_T(""));
	GetDlgItem(MAT_EDIT)->SetWindowText(_T(""));
	GetDlgItem(ENG_EDIT)->SetWindowText(_T(""));
}
