#include "pch.h"
#include "SQLInterface.h"

bool SQLInterface::Connect_MySQL()
{
    mysql_init(&mysqlCon);
    if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "stuinfo", 3306, NULL, 0)) {
        AfxMessageBox(_T("访问数据库失败！"));
        return false;
    }
    else {
        AfxMessageBox(_T("成功访问数据库！"));
        //设置字符集，使程序支持中文
        mysql_query(&mysqlCon, "SET NAMES 'GB2312'");   //解决从数据库中读取数据后汉字乱码显示的问题
    }
    return true;
}

vector<StuInfo> SQLInterface::Get_All_Info()
{
    vector<StuInfo> Info;

    // C语言组合字符串
    snprintf(sql, SQL_MAX, "SELECT * FROM info");

    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
    //判断查询结果
    if (ret) {
        AfxMessageBox(_T("查询失败！"));
        return Info;
    }

    // 获取结果集
    res = mysql_store_result(&mysqlCon);

    // 获取查询到的一行数据
    // 给row赋值，判断row是否为空，不为空就打印数据。
    while (row = mysql_fetch_row(res)) {
        StuInfo stuinfo = StuInfo(row[0], row[1], atoi(row[2]), stod(row[3]), stod(row[4]), stod(row[5]));
        Info.push_back(stuinfo);
    }

    // 释放结果集
    mysql_free_result(res);

    return Info;
}

bool SQLInterface::Add_Info(StuInfo Info)
{
    // C语言字符串组合  Info.m_name.c_str() 如果不加c_str就会报错，不知道为什么
    snprintf(sql, SQL_MAX, "INSERT INTO info VALUES('%s', '%s', %d, %lf, %lf, %lf);", 
        Info.m_name.c_str(), Info.m_sex.c_str(), Info.m_class_, Info.m_score1, Info.m_score2, Info.m_score3);
    //将上面拼接好的通过下面的函数发送给mysql数据库
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));

    //判断查询结果
    if (ret) {
        AfxMessageBox(_T("添加失败！"));
        return false;
    }

    return true;
}

bool SQLInterface::Del_Info(StuInfo Info)
{
    // C语言字符串组合
    snprintf(sql, SQL_MAX, "DELETE FROM info WHERE name = '%s';", Info.m_name.c_str());

    //将上面拼接好的通过下面的函数发送给mysql数据库
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));

    //判断查询结果
    if (ret) {
        AfxMessageBox(_T("删除失败！"));
        return false;
    }

    return true;
}

bool SQLInterface::UpdateInfo(StuInfo old_Info, StuInfo new_Info)
{
    // C语言组合字符串
    snprintf(sql, SQL_MAX, "UPDATE info SET name = '%s', sex = '%s', class_ = %d, score1 = %lf, score2 = %lf, score3 = %lf WHERE name = '%s';",
        new_Info.m_name.c_str(), new_Info.m_sex.c_str(), new_Info.m_class_, new_Info.m_score1, new_Info.m_score2, new_Info.m_score3, 
        old_Info.m_name.c_str());
    
    //将上面拼接好的通过下面的函数发送给mysql数据库
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));

    //判断查询结果
    if (ret) {
        AfxMessageBox(_T("修改失败！"));
        return false;
    }

    return true;
}

vector<StuInfo> SQLInterface::SeekInfo(CString name)
{
    vector<StuInfo> result;
    // C语言组合字符串
    snprintf(sql, SQL_MAX, "SELECT * FROM info WHERE name = '%s';", name);
    int ret = mysql_real_query(&mysqlCon, sql, (unsigned long)strlen(sql));
    //判断查询结果
    if (ret) {
        AfxMessageBox(_T("查询失败！"));
        return result;
    }

    // 获取结果集
    res = mysql_store_result(&mysqlCon);

    // 获取查询到的一行数据
    // 给row赋值，判断row是否为空，不为空就打印数据。
    while (row = mysql_fetch_row(res)) {
        StuInfo stuinfo = StuInfo(row[0], row[1], atoi(row[2]), stod(row[3]), stod(row[4]), stod(row[5]));
        result.push_back(stuinfo);
    }

    // 释放结果集
    mysql_free_result(res);

    return result;
}

void SQLInterface::ColseMysql()
{
    //关闭数据库
    mysql_close(&mysqlCon);
}
