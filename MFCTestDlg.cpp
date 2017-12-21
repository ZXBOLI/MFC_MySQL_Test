
// MFCTestDlg.cpp : 实现文件
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
#include <mysql.h> //mysql数据库自带的C API函数库，还需搭配函数库libmysql.lib和动态链接库libmysql.dll
#include <string>
#include <cstring>
#include <sstream> //类型转换专用

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql数据库的库函数


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCTestDlg 对话框



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


// CMFCTestDlg 消息处理程序

BOOL CMFCTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestDlg::OnQryButton() //当查询按钮被按下后，执行“查”操作
{
	// TODO:  在此添加控件通知处理程序代码
	const char user[] = "root"; //连接数据库的用户名
	const char pswd[] = "1111"; //密码
	const char host[] = "localhost"; //数据库地址，这里是做网络回环测试
	const char table[] = "students"; //数据库名
	unsigned int port = 3306; //端口号
	char sql[300]; //待加入参数的sql语句
	MYSQL myCont; //连接句柄
	MYSQL_RES *result; //查询结果
	MYSQL_ROW sql_row; //查询到的列，是一维数组形式，索引从0开始
	int res; //是否查询成功，返回值为bool类型
	CString local_id;
	GetDlgItemText(QRY_EDIT, local_id); //从空间QRY_EDIT中调用输入的值，类型为CString，存入local_id
	mysql_init(&myCont); //初始化连接
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0)) //realconnect为数据库是否连接成功的标志变量，返回bool类型
	{
		//重点，以下将控件传来的CString类型转为通常的char类型并加入到查询语句，char变量sql的需要的位置，以便于被mysql_query函数调用
		std::string id1;
		id1 = (char*)_bstr_t(local_id);
		char id3[100];
		const char *id2;
		id2 = id1.c_str();
		strcpy_s(id3, id2); //加入_s更安全
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		sprintf_s(sql, "select id, name, Chinese, Math, English from score where id = '%s';",id3); //加入_s更安全
		res = mysql_query(&myCont, sql);//实施“查”操作，函数mysql_query返回bool值，查询成功为true，反之为false
//		res = mysql_query(&myCont, "select id, name, Chinese, Math, English from score where id =3" );
		if (!res) //是否查询成功
		{
			result = mysql_store_result(&myCont); //是否返回结果集，若有，则返回一维数组格式的列查询结果，若没有，则返回空指针
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					/*
					重点，以下将查询返回的char*转换为控件能接受的int类型。可以使用万能数据转换类stringstream
					需要先在开头引入类库sstream
					对象stringstream和string数据类型都包含在名称空间std中，所以要先引用名称空间std
					万能数据类型转换对象stringstream使用：
					std::stringstream stream;
					std::string i = 1000;
					int result;
					stream << i; //将string类型输入流
					stream >> result; //从stream中抽取前面插入的string值，此时已转换为int类型
					下面的代码，为区分控件需要的整型与数据库传来的char类型，
					分别用ch_代表原本的char类型，in_代表转换后的int类型
					*/

					int in_id, in_chi, in_mat, in_eng;
					using namespace std;

					//学号
					string ch_id = sql_row[0];
					stringstream ss0;
					ss0 << ch_id;
					ss0 >> in_id;
					number = in_id;

					//name型本来就是String型，不需要转换
					name = sql_row[1];

					//语文成绩
					string ch_chi = sql_row[2];
					stringstream ss2;
					ss2 << ch_chi;
					ss2 >> in_chi;
					chinese_scr = in_chi;

					//数学成绩
					string ch_mat = sql_row[3];
					stringstream ss3;
					ss3 << ch_mat;
					ss3 >> in_mat;
					math_scr = in_mat;

					//英语成绩
					string ch_eng = sql_row[4];
					stringstream ss4;
					ss4 << ch_eng;
					ss4 >> in_eng;
					english_scr = in_eng;

					total = in_chi + in_mat + in_eng; //通过计算得出，数据库中无此字段

					average = (in_chi + in_mat + in_eng) / 3; //通过计算得出，数据库中无此字段


				}
			}
		}
		else
		{
			AfxMessageBox(_T("查询失败"));
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
	}
	//释放资源
	mysql_close(&myCont);
	UpdateData(FALSE);
}


void CMFCTestDlg::OnClickedAbout() //单击“关于”按钮，弹出项目自带的关于对话框
{
	// TODO:  在此添加控件通知处理程序代码
	Aboutbox aboutbox;
	aboutbox.DoModal();
}


void CMFCTestDlg::OnClickedAddButton() //单击添加按钮，弹出对话框添加学生
{
	// TODO:  在此添加控件通知处理程序代码
	Add add_dialog;
	add_dialog.DoModal();
}


void CMFCTestDlg::OnClickedDelButton() //按下删除按钮后
{
	// TODO:  在此添加控件通知处理程序代码
	Del del_dialog;
	del_dialog.DoModal();
}


void CMFCTestDlg::OnClickedModButton() //按下修改按钮后
{
	// TODO:  在此添加控件通知处理程序代码
	Mod mod_dialog;
	mod_dialog.DoModal();
}
