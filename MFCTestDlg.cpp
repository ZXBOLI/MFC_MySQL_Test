
// MFCTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCTest.h"
#include "MFCTestDlg.h"
#include "Aboutbox.h"
#include "Add.h"
#include "Del.h"
#include "Mod.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <mysql.h> //mysql���ݿ��Դ���C API�����⣬������亯����libmysql.lib�Ͷ�̬���ӿ�libmysql.dll
#include <string>
#include <cstring>
#include <sstream> //����ת��ר��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql���ݿ�Ŀ⺯��


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTestDlg �Ի���



CMFCTestDlg::CMFCTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTestDlg::IDD, pParent)
	, number(0)
	, name(_T(""))
	, chinese_scr(0)
	, math_scr(0)
	, english_scr(0)
	, average(0)
	, total(0)
	, search(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, NUM_EDIT, number);
	DDV_MinMaxInt(pDX, number, 0, 10);
	DDX_Text(pDX, NAM_EDIT, name);
	DDV_MaxChars(pDX, name, 20);
	DDX_Text(pDX, CHN_EDIT, chinese_scr);
	DDV_MinMaxInt(pDX, chinese_scr, 0, 100);
	DDX_Text(pDX, MAT_EDIT, math_scr);
	DDV_MinMaxInt(pDX, math_scr, 0, 100);
	DDX_Text(pDX, ENG_EDIT, english_scr);
	DDV_MinMaxInt(pDX, english_scr, 0, 100);
	DDX_Text(pDX, AVG_EDIT, average);
	DDV_MinMaxInt(pDX, average, 0, 100);
	DDX_Text(pDX, TOT_EDIT, total);
	DDV_MinMaxInt(pDX, total, 0, 300);
	//  DDX_Text(pDX, QRY_EDIT, search);
	//  DDV_MinMaxInt(pDX, search, 0, 10);
	DDX_Text(pDX, QRY_EDIT, search);
	DDV_MaxChars(pDX, search, 10);
}

BEGIN_MESSAGE_MAP(CMFCTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(QRY_BUTTON, &CMFCTestDlg::OnQryButton)
	ON_BN_CLICKED(IDC_ABOUT, &CMFCTestDlg::OnClickedAbout)
	ON_BN_CLICKED(ADD_BUTTON, &CMFCTestDlg::OnClickedAddButton)
	ON_BN_CLICKED(DEL_BUTTON, &CMFCTestDlg::OnClickedDelButton)
	ON_BN_CLICKED(MOD_BUTTON, &CMFCTestDlg::OnClickedModButton)
END_MESSAGE_MAP()


// CMFCTestDlg ��Ϣ�������

BOOL CMFCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestDlg::OnQryButton() //����ѯ��ť�����º�ִ�С��顱����
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	const char user[] = "root"; //�������ݿ���û���
	const char pswd[] = "1111"; //����
	const char host[] = "localhost"; //���ݿ��ַ��������������ػ�����
	const char table[] = "students"; //���ݿ���
	unsigned int port = 3306; //�˿ں�
	char sql[300]; //�����������sql���
	MYSQL myCont; //���Ӿ��
	MYSQL_RES *result; //��ѯ���
	MYSQL_ROW sql_row; //��ѯ�����У���һά������ʽ��������0��ʼ
	int res; //�Ƿ��ѯ�ɹ�������ֵΪbool����
	CString local_id;
	GetDlgItemText(QRY_EDIT, local_id); //�ӿռ�QRY_EDIT�е��������ֵ������ΪCString������local_id
	mysql_init(&myCont); //��ʼ������
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0)) //realconnectΪ���ݿ��Ƿ����ӳɹ��ı�־����������bool����
	{
		//�ص㣬���½��ؼ�������CString����תΪͨ����char���Ͳ����뵽��ѯ��䣬char����sql����Ҫ��λ�ã��Ա��ڱ�mysql_query��������
		std::string id1;
		id1 = (char*)_bstr_t(local_id);
		char id3[100];
		const char *id2;
		id2 = id1.c_str();
		strcpy_s(id3, id2); //����_s����ȫ
		mysql_query(&myCont, "SET NAMES GBK"); //���ñ����ʽ
		sprintf_s(sql, "select id, name, Chinese, Math, English from score where id = '%s';",id3); //����_s����ȫ
		res = mysql_query(&myCont, sql);//ʵʩ���顱����������mysql_query����boolֵ����ѯ�ɹ�Ϊtrue����֮Ϊfalse
//		res = mysql_query(&myCont, "select id, name, Chinese, Math, English from score where id =3" );
		if (!res) //�Ƿ��ѯ�ɹ�
		{
			result = mysql_store_result(&myCont); //�Ƿ񷵻ؽ���������У��򷵻�һά�����ʽ���в�ѯ�������û�У��򷵻ؿ�ָ��
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//��ȡ���������
				{
					/*
					�ص㣬���½���ѯ���ص�char*ת��Ϊ�ؼ��ܽ��ܵ�int���͡�����ʹ����������ת����stringstream
					��Ҫ���ڿ�ͷ�������sstream
					����stringstream��string�������Ͷ����������ƿռ�std�У�����Ҫ���������ƿռ�std
					������������ת������stringstreamʹ�ã�
					std::stringstream stream;
					std::string i = 1000;
					int result;
					stream << i; //��string����������
					stream >> result; //��stream�г�ȡǰ������stringֵ����ʱ��ת��Ϊint����
					����Ĵ��룬Ϊ���ֿؼ���Ҫ�����������ݿ⴫����char���ͣ�
					�ֱ���ch_����ԭ����char���ͣ�in_����ת�����int����
					*/

					int in_id, in_chi, in_mat, in_eng;
					using namespace std;

					//ѧ��
					string ch_id = sql_row[0];
					stringstream ss0;
					ss0 << ch_id;
					ss0 >> in_id;
					number = in_id;

					//name�ͱ�������String�ͣ�����Ҫת��
					name = sql_row[1];

					//���ĳɼ�
					string ch_chi = sql_row[2];
					stringstream ss2;
					ss2 << ch_chi;
					ss2 >> in_chi;
					chinese_scr = in_chi;

					//��ѧ�ɼ�
					string ch_mat = sql_row[3];
					stringstream ss3;
					ss3 << ch_mat;
					ss3 >> in_mat;
					math_scr = in_mat;

					//Ӣ��ɼ�
					string ch_eng = sql_row[4];
					stringstream ss4;
					ss4 << ch_eng;
					ss4 >> in_eng;
					english_scr = in_eng;

					total = in_chi + in_mat + in_eng; //ͨ������ó������ݿ����޴��ֶ�

					average = (in_chi + in_mat + in_eng) / 3; //ͨ������ó������ݿ����޴��ֶ�


				}
			}
		}
		else
		{
			AfxMessageBox(_T("��ѯʧ��"));
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


void CMFCTestDlg::OnClickedAbout() //���������ڡ���ť��������Ŀ�Դ��Ĺ��ڶԻ���
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Aboutbox aboutbox;
	aboutbox.DoModal();
}


void CMFCTestDlg::OnClickedAddButton() //������Ӱ�ť�������Ի������ѧ��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Add add_dialog;
	add_dialog.DoModal();
}


void CMFCTestDlg::OnClickedDelButton() //����ɾ����ť��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Del del_dialog;
	del_dialog.DoModal();
}


void CMFCTestDlg::OnClickedModButton() //�����޸İ�ť��
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	Mod mod_dialog;
	mod_dialog.DoModal();
}
