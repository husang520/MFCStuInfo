#pragma once


#include "StuInfo.h"

#define SQL_MAX 256		// sql����ַ��������ֵ


class SQLInterface
{
public:
	MYSQL_RES* res;	//result 
	MYSQL_ROW row;	//row	
	MYSQL mysqlCon; //connect
	char sql[SQL_MAX];		// �洢sql���

	bool Connect_MySQL();	//�������ݿ�

	vector<StuInfo> Get_All_Info();	//��ȡȫ����Ϣ

	bool Add_Info(StuInfo Info); //���ѧ����Ϣ

	bool Del_Info(StuInfo Info);	//ɾ��ѧ����Ϣ

	bool UpdateInfo(StuInfo old_Info, StuInfo new_Info);	//�޸�ѧ����Ϣ

	vector<StuInfo> SeekInfo(CString name);	//����ѧ����Ϣ

	void ColseMysql();	//�ر����ݿ�

};

