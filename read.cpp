#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using namespace std;

int main() {
    try {
        // MySQL Connector/C++ �ʱ�ȭ
        sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
        sql::Connection* con;
        sql::Statement* stmt;
        sql::ResultSet* res;

        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "user", "1234qwer*");
        con->setSchema("kdt_test"); // �����ͺ��̽� ����

        // �����ͺ��̽� ���� ����
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM member");

        // ��� ���
        while (res->next()) {
            cout << res->getString("name") << endl; // name �÷� ����ϰڴ�.
        }

        // MySQL Connector/C++ ����
        delete res;
        delete stmt;
        delete con;
    }
    catch (sql::SQLException& e) {
        cout << "MySQL error: " << e.getErrorCode() << " " << e.what() << endl;
    }

    return 0;
}