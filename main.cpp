#include <iostream>
#include <string>
#include <mysql/jdbc.h>
#include "Login.h"

using std::cout;
using std::endl;
using std::string;

const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "3432"; // �����ͺ��̽� ���� ��й�ȣ

//���̺� ���� �� ù��° ȸ���� ������ ����ִ´� 


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


        // �����ͺ��̽� ���� ����
        stmt = con->createStatement();
        stmt->execute("DROP TABLE IF EXISTS user"); // DROP
        cout << "Finished dropping table (if existed)" << endl;
        stmt->execute("CREATE TABLE user (id varchar(10) NOT NULL PRIMARY KEY ,pw varchar(20) NOT NULL,name varchar(10) NOT NULL,gender varchar(1) NOT NULL,birthday date NOT NULL,nickname varchar(10) NOT NULL);"); // CREATE
        cout << "Finished creating table" << endl;
        delete stmt;


       //ȸ��1 �� ���� �Է�

        pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // INSERT

        pstmt->setString(1, "sdd01");
        pstmt->setString(2, "0111");
        pstmt->setString(3, "Kimsu");
        pstmt->setString(4, "M");
        pstmt->setDateTime(5, "2001-11-20");
        pstmt->setString(6, "yoi");

        pstmt->execute();

        cout << "Complete" << endl;
        
        Login();  // �α��� �Լ� ���� 

         //MySQL Connector/C++ ����
        delete pstmt;
        delete con;

    


    return 0;
}