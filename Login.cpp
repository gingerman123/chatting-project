#include "Login.h"
#include <iostream>
#include<string>
#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using namespace std;

//���̵�� ��й�ȣ�� �Է¹޾� �����ϴ� ȸ������ Ȯ���ϱ� 

void Login() {
    string id;
    string pw;
    bool Login = true;
    bool again = true;
    bool exist = true;

    while(Login) {
        cout << "========LogIn========" << endl;
        cout << "ID: ";
        cin >> id;
        if (id == "���̵�ã��") {
            exist = true;
            again = false;
            findid();
        }
        if (id == "��й�ȣã��") {
            exist = true;
            again = false;
            findpw();
        }

        cout << "PW: ";
        cin >> pw;

        /*try {*/
            // MySQL Connector/C++ �ʱ�ȭ
            sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
            sql::Connection* con;
            sql::Statement* stmt;
            sql::ResultSet* res;

            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "3432");
            con->setSchema("chat"); // �����ͺ��̽� ����

            // �����ͺ��̽� ���� ����
            stmt = con->createStatement();
            res = stmt->executeQuery("SELECT * FROM user");

            

            // ���̵� Ȯ�� 
            while (res->next()) {

                if (res->getString("id") == id) {  // ���̵� ������ ��й�ȣ�� Ȯ�� 
                    exist = true;
                    if (res->getString("pw") == pw) { // ���̵� + ��й�ȣ �Ѵ� �°� �Է�-> �α��� ���� 
                        cout << "�α��� ����!" << endl;
                        Login = false;
                        again = false;
                        break;
                    }

                    else {
                        cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;  // ��й�ȣ�� Ʋ���� �� 
                    break;
                    }
                }

                else {
                    exist = false;
                }
                
            }

            if (exist ==false) {   // ���̵� �������� ���� ��� 
                cout << "�������� �ʴ� ȸ���Դϴ�" << endl;
            }
             
            if (again ==true) {   
                cout << "�ٽ� �Է��ϼ���" << endl;
            }


            // MySQL Connector/C++ ����
            delete res;
            delete stmt;
            delete con;
        //}


        /*catch (sql::SQLException& e) {
            cout << "MySQL error: " << e.getErrorCode() << " " << e.what() << endl;
        }*/

    }

}


void findid() {
    //���̵�ã�� ���
    sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "3432");
    con->setSchema("chat"); // �����ͺ��̽� ����

    // �����ͺ��̽� ���� ����
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM user");
    string name;
    string birthday;
    bool existid = true;
    
    system("cls");

    cout<< "�̸��� �Է��ϼ���: ";
    cin >> name;
    cout << "������ �Է��ϼ���(0000-00-00�������� �Է�): ";
    cin >> birthday;

    while (res->next()) {

        if (res->getString("name") == name) {
            if (res->getString("birthday") == birthday) {
                cout << "ȸ������ ���̵�� " << res->getString("id") << " �Դϴ�." << endl;  //�̸�+���� ��ġ -> id ���� 
                existid = true;
                exit(0);
            }
            else {
                existid = false;  //�̸���ġ+���Ϻ���ġ
                break;
            }
            
        }
        else {
            existid = false;
        }
    }

    if (existid == false) {
        cout << "�������� �ʴ� ȸ���Դϴ�. ȸ�������� ���ּ���." << endl;
        exit(0);
    }


}

void findpw() {
    //��й�ȣã�� ��� 
    sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "3432");
    con->setSchema("chat"); // �����ͺ��̽� ����

    // �����ͺ��̽� ���� ����
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM user");
    string id;
    string name;
    string birthday;
    bool existpw = true;

    system("cls");

    cout << "���̵� �Է��ϼ���: ";
    cin >> id;
    cout << "�̸��� �Է��ϼ���: ";
    cin >> name;
    cout << "������ �Է��ϼ���(0000-00-00�������� �Է�): ";
    cin >> birthday;

    while (res->next()) {

        if (res->getString("id") == id) {
            if (res->getString("name") == name) {
                if (res->getString("birthday") == birthday) {
                    cout << "ȸ������ ��й�ȣ�� " << res->getString("pw") << " �Դϴ�." << endl;  //�̸�+id+���� ��ġ -> pw ���� 
                    existpw = true;
                    exit(0);
                }
                else {
                    existpw = false;
                }
            }
            else {
                existpw = false;  //�̸���ġ+���Ϻ���ġ
                break;
            }

        }
        else {
            existpw = false;
        }
    }

    if (existpw == false) {
        cout << "�������� �ʴ� ȸ���Դϴ�. ȸ�������� ���ּ���." << endl;
        exit(0);
    }

}