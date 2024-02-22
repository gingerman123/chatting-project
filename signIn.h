#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <mysql/jdbc.h>

using namespace std;

void create(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt);
void signin(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::PreparedStatement* pstmt);