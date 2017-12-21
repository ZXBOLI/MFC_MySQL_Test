// Add.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Add.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <mysql.h>
#include <string>
#include <cstring>
#include <sstream>

#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql���ݿ�Ŀ⺯��


// Add �Ի���

IMPLEMENT_DYNAMIC(Add, CDialogEx)

Add::Add(CWnd* pParent /*=NULL*/)
	: CDialogEx(Add::IDD, pParent)
	, name(_T(""))
	, math_scr(_T(""))
	, chinese_scr(_T(""))
	, english_scr(_T(""))
{

}

Add::~Add()
{
}

void Add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, NAM_EDIT, name);
	DDV_MaxChars(pDX, name, 20);
	//  DDX_Text(pDX, MAT_EDIT, math_scr);
	DDX_Text(pDX, MAT_EDIT, math_scr);
	DDX_Text(pDX, CHN_EDIT, chinese_scr);
	DDX_Text(pDX, ENG_EDIT, english_scr);
}


BEGIN_MESSAGE_MAP(Add, CDialogEx)
	ON_BN_CLICKED(IDOK, &Add::OnBnClickedOk)
	ON_BN_CLICKED(RST_BUTTON, &Add::OnClickedRstButton)
END_MESSAGE_MAP()


// Add ��Ϣ�������


void Add::OnBnClickedOk() //����ȷ�ϰ�ť��ִ�С���������
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	const char user[] = "root"; //�������ݿ���û���
	const char pswd[] = "1111"; //����
	const char host[] = "localhost"; //���ݿ��ַ��������������ػ�����
	const char table[] = "students"; //���ݿ���
	unsigned int port = 3306; //�˿ں�
	char sql[300]; //�����������sql���
	MYSQL myCont; //���Ӿ��
	int res; //�Ƿ��ѯ�ɹ�������ֵΪbool����
	CString local_name;
	CString local_chinese;
	CString local_math;
	CString local_english;
	//��ÿ���ı�����ȡ��ֵ�����������ֶ���CString��תΪchar*�ͣ��Ա��ڲ�����sql���
	GetDlgItemText(NAM_EDIT, local_name);
	GetDlgItemText(CHN_EDIT, local_chinese);
	GetDlgItemText(MAT_EDIT, local_math);
	GetDlgItemText(ENG_EDIT, local_english);
	int len1 = WideCharToMultiByte(CP_ACP, 0, local_name, -1, NULL, 0, NULL, NULL);
	int len2 = WideCharToMultiByte(CP_ACP, 0, local_chinese, -1, NULL, 0, NULL, NULL);
	int len3 = WideCharToMultiByte(CP_ACP, 0, local_math, -1, NULL, 0, NULL, NULL);
	int len4 = WideCharToMultiByte(CP_ACP, 0, local_english, -1, NULL, 0, NULL, NULL);
	char *chr_name = new char[len1 + 1];
	char *chr_chn = new char[len2 + 1];
	char *chr_mat = new char[len3 + 1];
	char *chr_eng = new char[len4 + 1];
	WideCharToMultiByte(CP_ACP, 0, local_name, -1, chr_name, len1, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, local_chinese, -1, chr_chn, len2, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, local_math, -1, chr_mat, len3, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, local_english, -1, chr_eng, len4, NULL, NULL);
	//���ɼ���CString��תΪint�ͣ��Ա��ں��������ֵȡֵ�߽����
	int i_chi;
	int i_mat;
	int i_eng;
	swscanf_s(local_chinese,_T("%d"),&i_chi);
	swscanf_s(local_math, _T("%d"), &i_mat);
	swscanf_s(local_english, _T("%d"), &i_eng);
	mysql_init(&myCont); //��ʼ������
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0)) //realconnectΪ���ݿ��Ƿ����ӳɹ��ı�־����������bool����
	{
		if (!(i_chi > 100 || i_mat > 100 || i_eng > 100)) //��ֵȡֵ�߽�������������ܴ���100����Ϊ������Դ��ͼ�н������ı����number������Ϊtrue�����Բ����ܻ����븺�ţ���˲��ü��ֵΪ�������
		{
			char sql[300];
			sprintf_s(sql, "insert into score(name, Chinese, Math, English) values('%s', '%s', '%s', '%s')", chr_name, chr_chn, chr_mat, chr_eng); //��ת���õ��ֶβ�����sql���
			mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
			res = mysql_query(&myCont, sql); //ʵʩ����������������mysql_query����boolֵ����ӳɹ�Ϊtrue����֮Ϊfalse
			if (res == 0){
				AfxMessageBox(_T("����ɹ�"));
				CDialogEx::OnOK(); //��ѯ�ɹ��������Ի�����ΪOK״̬���˳�
				//CStringתchar*�Ĺ���������new�����ڴ�ռ䣬��������Ҫ��delete���
				delete[] chr_name;
				delete[] chr_chn;
				delete[] chr_mat;
				delete[] chr_eng;
			}
			else
			{
				AfxMessageBox(_T("����ʧ��"));
				//��ʹ����ʧ��Ҳ��Ҫ����ڴ�
				delete[] chr_name;
				delete[] chr_chn;
				delete[] chr_mat;
				delete[] chr_eng;
			}
		}
		else
		{
			AfxMessageBox(_T("���ݲ��ڷ�Χ��\n������Χ��0��100"));
			//��ʹ�������ݲ��Ϸ�Ҳ��Ҫ����ڴ�
			delete[] chr_name;
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

void Add::OnClickedRstButton() //�������ð�ť��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ָ�뷨��տؼ���ֵ
	GetDlgItem(NAM_EDIT)->SetWindowText(_T(""));
	GetDlgItem(CHN_EDIT)->SetWindowText(_T(""));
	GetDlgItem(MAT_EDIT)->SetWindowText(_T(""));
	GetDlgItem(ENG_EDIT)->SetWindowText(_T(""));
}
