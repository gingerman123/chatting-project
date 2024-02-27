#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mysql/jdbc.h>
#include <chrono>
#include <ctime>

using namespace std;

void create_t(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt);
void signin_t(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::PreparedStatement* pstmt,std::string id_1,std::string pw_1);
void create(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt);
void signin(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::PreparedStatement* pstmt);