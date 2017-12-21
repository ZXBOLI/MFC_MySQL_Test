// Mod.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTest.h"
#include "Mod.h"
#include "afxdialogex.h"
#include <mysql.h> //mysql数据库自带的C API函数库，还需搭配函数库libmysql.lib和动态链接库libmysql.dll
#include <string>
#include <cstring>
#include <sstream> //类型转换专用

#pragma comment(lib,"G:\\Program Files (x86)\\MySQL\\MySQL Server 5.1\\lib\\opt\\libmysql.lib") //mysql数据库的库函数


// Mod 对话框

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


// Mod 消息处理程序


BOOL Mod::OnInitDialog() //初始化对话框后的事件
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	/*
	注：在新版Visual C++中，对话框的OnInitDialog消息已变更为虚函数
	重点：若想要动态设置一个组合框里的值，就需要编写一个对话框初始化事件虚函数
	*/
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


void Mod::OnSelchangeCombo() //当组合框选项变化时
{
	// TODO:  在此添加控件通知处理程序代码
	/*
	重点：关于ComboBox的控件事件CBN_SELCHANGE的索引加取值问题
	关键点就是执行顺序和执行了什么的问题？

	当触发CBN_SELCHANGE消息时，这时combobox中的索引值改变，但是这时候的文字框里面的内容没有改变。
	这时GetWindowText()肯定得到的是先前的内容（相对于想要的）。这以后，在完成关联变量的更新，combobox里面出现想要的内容。
	因此，欲根治该问题，就必须对索引值下手
	*/
	int index = ((CComboBox*)GetDlgItem(ID_COMBO))->GetCurSel(); //获得想要的索引值  
	((CComboBox*)GetDlgItem(ID_COMBO))->SetCurSel(index); //设置成想要索引值的值  
	UpdateData(true);
	CString selid;
	((CComboBox*)GetDlgItem(ID_COMBO))->GetWindowText(selid);
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


void Mod::OnBnClickedOk() //当确定按钮被按下后，执行“改”操作
{
	// TODO:  在此添加控件通知处理程序代码
		int index = ((CComboBox*)GetDlgItem(ID_COMBO))->GetCurSel(); //获得想要的索引值  
		((CComboBox*)GetDlgItem(ID_COMBO))->SetCurSel(index); //设置成想要索引值的值  
		UpdateData(true);
		CString selid;
		((CComboBox*)GetDlgItem(ID_COMBO))->GetWindowText(selid);
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
		CString local_chinese;
		CString local_math;
		CString local_english;
		//从每个文本框中取得值，并将各个字段由CString型转为char*型，以便于插入至sql语句，但此时name不用修改
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
		//将成绩由CString型转为int型，以便于后面进行数值取值边界分析
		int i_chi;
		int i_mat;
		int i_eng;
		swscanf_s(local_chinese, _T("%d"), &i_chi);
		swscanf_s(local_math, _T("%d"), &i_mat);
		swscanf_s(local_english, _T("%d"), &i_eng);
		mysql_init(&myCont); //初始化连接
		if (mysql_real_connect(&myCont, host, user, pswd, table, port, NULL, 0))
		{
			if (!(i_chi > 100 || i_mat > 100 || i_eng > 100)) //数值取值边界分析，分数不能大于100。因为已在资源视图中将分数文本框的number属性设为true，所以不可能会输入负号，因此不用检查值为负的情况
			{
				mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式
				sprintf_s(sql2, "update score set Chinese ='%s',Math ='%s',English ='%s' where id = '%s';", chr_chn, chr_mat, chr_eng, chr_id); //将转换后的字段加入sql语句中
				res = mysql_query(&myCont, sql2);//实施“改”操作，函数mysql_query返回bool值，修改成功为true，反之为false
				if (res == 0)
				{
					AfxMessageBox(_T("更新成功"));
					CDialogEx::OnOK();
					//CString转char*的过程中有用new分配内存空间，在这里需要用delete清空
					delete[] chr_chn;
					delete[] chr_mat;
					delete[] chr_eng;
				}
				else
				{
					AfxMessageBox(_T("更新失败"));
					//即使更新失败也需要清空内存
					delete[] chr_chn;
					delete[] chr_mat;
					delete[] chr_eng;
				}
			}
			else
			{
				AfxMessageBox(_T("数据不在范围中\n分数范围：0到100"));
				//即使输入数据不合法也需要清空内存
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

void Mod::OnClickedRstButton() //按下重置按钮后
{
	// TODO:  在此添加控件通知处理程序代码
	//用指针法清空控件的值
	GetDlgItem(CHN_EDIT)->SetWindowText(_T(""));
	GetDlgItem(MAT_EDIT)->SetWindowText(_T(""));
	GetDlgItem(ENG_EDIT)->SetWindowText(_T(""));
}
