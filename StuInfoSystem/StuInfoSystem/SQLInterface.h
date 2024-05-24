#pragma once


#include "StuInfo.h"

#define SQL_MAX 256		// sql语句字符数组最大值


class SQLInterface
{
public:
	MYSQL_RES* res;	//result 
	MYSQL_ROW row;	//row	
	MYSQL mysqlCon; //connect
	char sql[SQL_MAX];		// 存储sql语句

	bool Connect_MySQL();	//连接数据库

	vector<StuInfo> Get_All_Info();	//获取全部信息

	bool Add_Info(StuInfo Info); //添加学生信息

	bool Del_Info(StuInfo Info);	//删除学生信息

	bool UpdateInfo(StuInfo old_Info, StuInfo new_Info);	//修改学生信息

	vector<StuInfo> SeekInfo(CString name);	//查找学生信息

	void ColseMysql();	//关闭数据库

};

