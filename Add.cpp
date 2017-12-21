// Add.cpp : 实现文件
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

#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql数据库的库函数


// Add 对话框

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


// Add 消息处理程序


void Add::OnBnClickedOk() //按下确认按钮后，执行“增”操作
{
	// TODO:  在此添加控件通知处理程序代码
	const char user[] = "root"; //连接数据库的用户名
	const char pswd[] = "1111"; //密码
	const char host[] = "localhost"; //数据库地址，这里是做网络回环测试
	const char table[] = "students"; //数据库名
	unsigned int port = 3306; //端口号
	char sql[300]; //待加入参数的sql语句
	MYSQL myCont; //连接句柄
	int res; //是否查询成功，返回值为bool类型
	CString local_name;
	CString local_chinese;
	CString local_math;
	CString local_english;
	//从每个文本框中取得值，并将各个字段由CString型转为char*型，以便于插入至sql语句
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
	//将成绩由CString型转为int型，以便于后面进行数值取值边界分析
	int i_chi;
	int i_mat;
	int i_eng;
	swscanf_s(local_chinese,_T("%d"),&i_chi);
	swscanf_s(local_math, _T("%d"), &i_mat);
	swscanf_s(local_english, _T("%d"), &i_eng);
	mysql_init(&myCont); //初始化连接
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0)) //realconnect为数据库是否连接成功的标志变量，返回bool类型
	{
		if (!(i_chi > 100 || i_mat > 100 || i_eng > 100)) //数值取值边界分析，分数不能大于100。因为已在资源视图中将分数文本框的number属性设为true，所以不可能会输入负号，因此不用检查值为负的情况
		{
			char sql[300];
			sprintf_s(sql, "insert into score(name, Chinese, Math, English) values('%s', '%s', '%s', '%s')", chr_name, chr_chn, chr_mat, chr_eng); //将转换好的字段插入至sql语句
			mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
			res = mysql_query(&myCont, sql); //实施“增”操作，函数mysql_query返回bool值，添加成功为true，反之为false
			if (res == 0){
				AfxMessageBox(_T("插入成功"));
				CDialogEx::OnOK(); //查询成功，即将对话框置为OK状态并退出
				//CString转char*的过程中有用new分配内存空间，在这里需要用delete清空
				delete[] chr_name;
				delete[] chr_chn;
				delete[] chr_mat;
				delete[] chr_eng;
			}
			else
			{
				AfxMessageBox(_T("插入失败"));
				//即使插入失败也需要清空内存
				delete[] chr_name;
				delete[] chr_chn;
				delete[] chr_mat;
				delete[] chr_eng;
			}
		}
		else
		{
			AfxMessageBox(_T("数据不在范围中\n分数范围：0到100"));
			//即使输入数据不合法也需要清空内存
			delete[] chr_name;
			delete[] chr_chn;
			delete[] chr_mat;
			delete[] chr_eng;
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

void Add::OnClickedRstButton() //按下重置按钮后
{
	// TODO:  在此添加控件通知处理程序代码
	//用指针法清空控件的值
	GetDlgItem(NAM_EDIT)->SetWindowText(_T(""));
	GetDlgItem(CHN_EDIT)->SetWindowText(_T(""));
	GetDlgItem(MAT_EDIT)->SetWindowText(_T(""));
	GetDlgItem(ENG_EDIT)->SetWindowText(_T(""));
}
