// Del.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Del.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <mysql.h> //mysql数据库自带的C API函数库，还需搭配函数库libmysql.lib和动态链接库libmysql.dll
#include <string>
#include <cstring>
#include <sstream> //类型转换专用

#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql数据库的库函数

// Del 对话框

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


// Del 消息处理程序




BOOL Del::OnInitDialog()
{
	/*
	注：在新版Visual C++中，对话框的OnInitDialog消息已变更为虚函数
	重点：若想要动态设置一个组合框里的值，就需要编写一个对话框初始化事件虚函数
	*/
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	
	const char user[] = "root"; //连接数据库的用户名
	const char pswd[] = "1111"; //密码
	const char host[] = "localhost"; //数据库地址，这里是做网络回环测试
	const char table[] = "students"; //数据库名
	unsigned int port = 3306; //端口号
	MYSQL myCont; //连接句柄
	MYSQL_RES *result; //查询结果
	MYSQL_ROW sql_row; //查询到的列，是一维数组形式，索引从0开始
	int res; //是否查询成功，返回值为bool类型
	mysql_init(&myCont); //初始化连接
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		res = mysql_query(&myCont, "select id from score");
		if (!res)
		{
			result = mysql_store_result(&myCont); //是否返回结果集，若有，则返回一维数组格式的列查询结果，若没有，则返回空指针
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//通过while循环，一点点把组合框里的项填满
				{
					//重点：必须先将数据库查询返回的char*型转为CString型才能被组合框的AddString方法使用，否则会乱码
					char *q = sql_row[0];
					CString qid(q);
					m_Combo1.AddString(qid);

				}
			}
		}
		else
		{
			AfxMessageBox(_T("失败，未查询到ID"));
		}
	}
	else
	{
		AfxMessageBox(_T("数据库连接失败"));
	}
	//释放资源
	mysql_close(&myCont);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void Del::OnSelchangeDelid()
{
	// TODO:  在此添加控件通知处理程序代码
	/*
	重点：关于ComboBox的控件事件CBN_SELCHANGE的索引加取值问题
	关键点就是执行顺序和执行了什么的问题？

	当触发CBN_SELCHANGE消息时，这时combobox中的索引值改变，但是这时候的文字框里面的内容没有改变。
	这时GetWindowText()肯定得到的是先前的内容（相对于想要的）。这以后，在完成关联变量的更新，combobox里面出现想要的内容。
	因此，欲根治该问题，就必须对索引值下手！
	*/
	int index = ((CComboBox*)GetDlgItem(IDC_DELID))->GetCurSel(); //获得想要的索引值  
	((CComboBox*)GetDlgItem(IDC_DELID))->SetCurSel(index); //设置成想要索引值的值  
	UpdateData(true);
	CString selid;
	((CComboBox*)GetDlgItem(IDC_DELID))->GetWindowText(selid);
	int len1 = WideCharToMultiByte(CP_ACP, 0, selid, -1, NULL, 0, NULL, NULL);
	char *chr_id = new char[len1 + 1];
	WideCharToMultiByte(CP_ACP, 0, selid, -1, chr_id, len1, NULL, NULL);
	const char user[] = "root"; //连接数据库的用户名
	const char pswd[] = "1111"; //密码
	const char host[] = "localhost"; //数据库地址，这里是做网络回环测试
	const char table[] = "students"; //数据库名
	unsigned int port = 3306; //端口号
	char sql1[300]; //待加入参数的sql语句
	MYSQL myCont; //连接句柄
	MYSQL_RES *result; //查询结果
	MYSQL_ROW sql_row; //查询到的列，是一维数组形式，索引从0开始
	int res; //是否查询成功，返回值为bool类型
	mysql_init(&myCont); //初始化连接
	if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
	{
		mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
		sprintf_s(sql1, "select id, name, Chinese, Math, English from score where id = '%s';", chr_id); //加入_s更安全
		res = mysql_query(&myCont, sql1);//实施查询，函数mysql_query返回bool值，查询成功为true，反之为false
		if (!res) //是否查询成功
		{
			result = mysql_store_result(&myCont); //是否返回结果集，若有，则返回一维数组格式的列查询结果，若没有，则返回空指针
			if (result)
			{
				while (sql_row = mysql_fetch_row(result))//获取具体的数据
				{
					name = sql_row[1];
					chinese_scr = sql_row[2];
					math_scr = sql_row[3];
					english_scr = sql_row[4];
				}
			}
			else
			{
				AfxMessageBox(_T("查询失败"));
			}
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


void Del::OnClickedDltButton() //按下删除按钮，执行“删”操作
{
	// TODO:  在此添加控件通知处理程序代码
	if (MessageBox(_T("确认删除？"), _T("删除"), MB_ICONQUESTION | MB_OKCANCEL) == IDOK) //弹出一个确认对话框，确认是否执行删除
	{
		/*
		重点：关于ComboBox的控件事件CBN_SELCHANGE的索引加取值问题
		关键点就是执行顺序和执行了什么的问题？

		当触发CBN_SELCHANGE消息时，这时combobox中的索引值改变，但是这时候的文字框里面的内容没有改变。
		这时GetWindowText()肯定得到的是先前的内容（相对于想要的）。这以后，在完成关联变量的更新，combobox里面出现想要的内容。
		因此，欲根治该问题，就必须对索引值下手
		*/
		int index = ((CComboBox*)GetDlgItem(IDC_DELID))->GetCurSel(); //获得想要的索引值  
		((CComboBox*)GetDlgItem(IDC_DELID))->SetCurSel(index); //设置成想要索引值的值  
		UpdateData(true); //来获取关联变量，即改变后的值
		CString selid;
		((CComboBox*)GetDlgItem(IDC_DELID))->GetWindowText(selid);
		//CString转char*，以便于放入sql语句中
		int len1 = WideCharToMultiByte(CP_ACP, 0, selid, -1, NULL, 0, NULL, NULL);
		char *chr_id = new char[len1 + 1];
		WideCharToMultiByte(CP_ACP, 0, selid, -1, chr_id, len1, NULL, NULL);
		const char user[] = "root"; //连接数据库的用户名
		const char pswd[] = "1111"; //密码
		const char host[] = "localhost"; //数据库地址，这里是做网络回环测试
		const char table[] = "students"; //数据库名
		unsigned int port = 3306; //端口号
		char sql2[300]; //待加入参数的sql语句
		MYSQL myCont; //连接句柄
		MYSQL_RES *result; //查询结果
		MYSQL_ROW sql_row; //查询到的列，是一维数组形式，索引从0开始
		int res; //是否查询成功，返回值为bool类型
		mysql_init(&myCont); //初始化连接
		if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
		{
			mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
			sprintf_s(sql2, "delete from score where id = '%s';", chr_id); //删除操作
			res = mysql_query(&myCont, sql2);//实施“删”操作，函数mysql_query返回bool值，删除成功为true，反之为false
			if (res == 0)
			{
				AfxMessageBox(_T("删除成功"));
				CDialogEx::OnOK(); //将对话框置于OK状态并退出
			}
			else
			{
				AfxMessageBox(_T("删除失败"));
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
	else
	{
		return; //这里指的是确认删除操作的对话框若点了取消，则返回
	}
}
