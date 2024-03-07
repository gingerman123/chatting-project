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
//테이블 이름 입력하고 테이블 만들기


void create_t(MySQL_Driver* driver, Connection* con, Statement* stmt, const string& table_name);
//id,pw에 값 넣기
void signin_t(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt,std::string id_1,std::string pw_1);
// user 테이블 만들기
void create(MySQL_Driver* driver, Connection* con, Statement* stmt);
// 조건 모두 검사하고 회원가입하기(값 넣기)
void signin(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt);
// id 테이블에 접근해서 pw가 맞는지 체크
string check_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt,ResultSet* res,const string& id,const string& pw);
// 비밀번호 찾기
string find_pw(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id, const string& birth);
// id 찾기
string find_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& name, const string& birth);
// 닉네임 찾기
string find_nickname(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id);
// id 중복 체크
string isdup(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id);
void reg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, const string& id, const string& pw, const string& name, const string& gender, const string& birthday, const string& nickname);
void save_msg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt,const string& nickname,const string& msg,const string& date,const string& time);