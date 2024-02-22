#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using std::cout;
using std::endl;
using std::string;

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
    con->setSchema("mysql1");

    // db �ѱ� ������ ���� ���� 
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }

    // �����ͺ��̽� ���� ����
    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS inventory"); // DROP
    cout << "Finished dropping table (if existed)" << endl;
    stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);"); // CREATE
    cout << "Finished creating table" << endl;
    delete stmt;

    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)"); // INSERT
    string a = "�����";
    pstmt->setString(1, a);
    pstmt->setInt(2, 150);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "orange");
    pstmt->setInt(2, 154);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "���");
    pstmt->setInt(2, 100);
    pstmt->execute();
    cout << "One row inserted." << endl;

    // MySQL Connector/C++ ����
    delete pstmt;
    delete con;

    return 0;
}