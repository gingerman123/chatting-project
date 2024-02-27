#include <iostream>
#include <string>
#include "signIn.h"

using namespace std;

const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "wndud0602!"; // �����ͺ��̽� ���� ��й�ȣ

int main()
{
	// MySQL Connector/C++ �ʱ�ȭ
	sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
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

	// �����ͺ��̽� ����
	con->setSchema("chat");

	// db �ѱ� ������ ���� ���� 
	stmt = con->createStatement();
	stmt->execute("set names euckr");
	if (stmt) { delete stmt; stmt = nullptr; }

	create(driver,con,stmt);
	pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user ���̺� insert
	signin(driver,con,stmt,pstmt);


	return 0;

}