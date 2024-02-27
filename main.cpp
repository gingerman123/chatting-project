#include <iostream>
#include <string>
#include "signIn.h"

using namespace std;

const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
const string username = "root"; // 데이터베이스 사용자
const string password = "wndud0602!"; // 데이터베이스 접속 비밀번호

int main()
{
	// MySQL Connector/C++ 초기화
	sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	try {
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException& e) {
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		exit(1);
	}

	// 데이터베이스 선택
	con->setSchema("chat");

	// db 한글 저장을 위한 셋팅 
	stmt = con->createStatement();
	stmt->execute("set names euckr");
	if (stmt) { delete stmt; stmt = nullptr; }

	create(driver,con,stmt);
	pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user 테이블 insert
	signin(driver,con,stmt,pstmt);


	return 0;

}