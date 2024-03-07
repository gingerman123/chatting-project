#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mysql/jdbc.h>
#include <chrono>
#include <ctime>

using namespace std;
using namespace sql;
using namespace mysql;
//���̺� �̸� �Է��ϰ� ���̺� �����


void create_t(MySQL_Driver* driver, Connection* con, Statement* stmt, const string& table_name);
//id,pw�� �� �ֱ�
void signin_t(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt,std::string id_1,std::string pw_1);
// user ���̺� �����
void create(MySQL_Driver* driver, Connection* con, Statement* stmt);
// ���� ��� �˻��ϰ� ȸ�������ϱ�(�� �ֱ�)
void signin(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt);
// id ���̺� �����ؼ� pw�� �´��� üũ
string check_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt,ResultSet* res,const string& id,const string& pw);
// ��й�ȣ ã��
string find_pw(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id, const string& birth);
// id ã��
string find_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& name, const string& birth);
// �г��� ã��
string find_nickname(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id);
// id �ߺ� üũ
string isdup(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id);
void reg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, const string& id, const string& pw, const string& name, const string& gender, const string& birthday, const string& nickname);
void save_msg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt,const string& nickname,const string& msg,const string& date,const string& time);