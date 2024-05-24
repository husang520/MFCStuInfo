#include "pch.h"
#include "SQLInterface.h"

bool SQLInterface::Connect_MySQL()
{
    mysql_init(&mysqlCon);
    if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "stuinfo", 3306, NULL, 0)) {
        AfxMessageBox(_T("�������ݿ�ʧ�ܣ�"));
        return false;
    }
    else {
        AfxMessageBox(_T("�ɹ��������ݿ⣡"));
        //�����ַ�����ʹ����֧������
        mysql_query(&mysqlCon, "SET NAMES 'GB2312'");   //��������ݿ��ж�ȡ���ݺ���������ʾ������
    }
    return true;
}

vector<StuInfo> SQLInterface::Get_All_Info()
{
    vector<StuInfo> Info;

    // C��������ַ���
    snprintf(sql, SQL_MAX, "SELECT * FROM info");

    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
    //�жϲ�ѯ���
    if (ret) {
        AfxMessageBox(_T("��ѯʧ�ܣ�"));
        return Info;
    }

    // ��ȡ�����
    res = mysql_store_result(&mysqlCon);

    // ��ȡ��ѯ����һ������
    // ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
    while (row = mysql_fetch_row(res)) {
        StuInfo stuinfo = StuInfo(row[0], row[1], atoi(row[2]), stod(row[3]), stod(row[4]), stod(row[5]));
        Info.push_back(stuinfo);
    }

    // �ͷŽ����
    mysql_free_result(res);

    return Info;
}

bool SQLInterface::Add_Info(StuInfo Info)
{
    // C�����ַ������  Info.m_name.c_str() �������c_str�ͻᱨ����֪��Ϊʲô
    snprintf(sql, SQL_MAX, "INSERT INTO info VALUES('%s', '%s', %d, %lf, %lf, %lf);", 
        Info.m_name.c_str(), Info.m_sex.c_str(), Info.m_class_, Info.m_score1, Info.m_score2, Info.m_score3);
    //������ƴ�Ӻõ�ͨ������ĺ������͸�mysql���ݿ�
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));

    //�жϲ�ѯ���
    if (ret) {
        AfxMessageBox(_T("���ʧ�ܣ�"));
        return false;
    }

    return true;
}

bool SQLInterface::Del_Info(StuInfo Info)
{
    // C�����ַ������
    snprintf(sql, SQL_MAX, "DELETE FROM info WHERE name = '%s';", Info.m_name.c_str());

    //������ƴ�Ӻõ�ͨ������ĺ������͸�mysql���ݿ�
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));

    //�жϲ�ѯ���
    if (ret) {
        AfxMessageBox(_T("ɾ��ʧ�ܣ�"));
        return false;
    }

    return true;
}

bool SQLInterface::UpdateInfo(StuInfo old_Info, StuInfo new_Info)
{
    // C��������ַ���
    snprintf(sql, SQL_MAX, "UPDATE info SET name = '%s', sex = '%s', class_ = %d, score1 = %lf, score2 = %lf, score3 = %lf WHERE name = '%s';",
        new_Info.m_name.c_str(), new_Info.m_sex.c_str(), new_Info.m_class_, new_Info.m_score1, new_Info.m_score2, new_Info.m_score3, 
        old_Info.m_name.c_str());
    
    //������ƴ�Ӻõ�ͨ������ĺ������͸�mysql���ݿ�
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));

    //�жϲ�ѯ���
    if (ret) {
        AfxMessageBox(_T("�޸�ʧ�ܣ�"));
        return false;
    }

    return true;
}

vector<StuInfo> SQLInterface::SeekInfo(CString name)
{
    vector<StuInfo> result;
    // C��������ַ���
    snprintf(sql, SQL_MAX, "SELECT * FROM info WHERE name = '%s';", name);
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
    //�жϲ�ѯ���
    if (ret) {
        AfxMessageBox(_T("��ѯʧ�ܣ�"));
        return result;
    }

    // ��ȡ�����
    res = mysql_store_result(&mysqlCon);

    // ��ȡ��ѯ����һ������
    // ��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
    while (row = mysql_fetch_row(res)) {
        StuInfo stuinfo = StuInfo(row[0], row[1], atoi(row[2]), stod(row[3]), stod(row[4]), stod(row[5]));
        result.push_back(stuinfo);
    }

    // �ͷŽ����
    mysql_free_result(res);

    return result;
}

void SQLInterface::ColseMysql()
{
    //�ر����ݿ�
    mysql_close(&mysqlCon);
}
