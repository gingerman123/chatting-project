#include "Login.h"
#include <iostream>
#include<string>
#include <iostream>
#include <string>
#include <mysql/jdbc.h>

using namespace std;

//아이디와 비밀번호를 입력받아 존재하는 회원인지 확인하기 

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
        if (id == "아이디찾기") {
            exist = true;
            again = false;
            findid();
        }
        if (id == "비밀번호찾기") {
            exist = true;
            again = false;
            findpw();
        }

        cout << "PW: ";
        cin >> pw;

        /*try {*/
            // MySQL Connector/C++ 초기화
            sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
            sql::Connection* con;
            sql::Statement* stmt;
            sql::ResultSet* res;

            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "3432");
            con->setSchema("chat"); // 데이터베이스 선택

            // 데이터베이스 쿼리 실행
            stmt = con->createStatement();
            res = stmt->executeQuery("SELECT * FROM user");

            

            // 아이디 확인 
            while (res->next()) {

                if (res->getString("id") == id) {  // 아이디가 맞으면 비밀번호도 확인 
                    exist = true;
                    if (res->getString("pw") == pw) { // 아이디 + 비밀번호 둘다 맞게 입력-> 로그인 성공 
                        cout << "로그인 성공!" << endl;
                        Login = false;
                        again = false;
                        break;
                    }

                    else {
                        cout << "비밀번호가 틀렸습니다." << endl;  // 비밀번호만 틀렸을 때 
                    break;
                    }
                }

                else {
                    exist = false;
                }
                
            }

            if (exist ==false) {   // 아이디가 존재하지 않을 경우 
                cout << "존재하지 않는 회원입니다" << endl;
            }
             
            if (again ==true) {   
                cout << "다시 입력하세요" << endl;
            }


            // MySQL Connector/C++ 정리
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
    //아이디찾기 기능
    sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "3432");
    con->setSchema("chat"); // 데이터베이스 선택

    // 데이터베이스 쿼리 실행
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM user");
    string name;
    string birthday;
    bool existid = true;
    
    system("cls");

    cout<< "이름을 입력하세요: ";
    cin >> name;
    cout << "생일을 입력하세요(0000-00-00형식으로 입력): ";
    cin >> birthday;

    while (res->next()) {

        if (res->getString("name") == name) {
            if (res->getString("birthday") == birthday) {
                cout << "회원님의 아이디는 " << res->getString("id") << " 입니다." << endl;  //이름+생일 일치 -> id 제공 
                existid = true;
                exit(0);
            }
            else {
                existid = false;  //이름일치+생일불일치
                break;
            }
            
        }
        else {
            existid = false;
        }
    }

    if (existid == false) {
        cout << "존재하지 않는 회원입니다. 회원가입을 해주세요." << endl;
        exit(0);
    }


}

void findpw() {
    //비밀번호찾기 기능 
    sql::mysql::MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "3432");
    con->setSchema("chat"); // 데이터베이스 선택

    // 데이터베이스 쿼리 실행
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM user");
    string id;
    string name;
    string birthday;
    bool existpw = true;

    system("cls");

    cout << "아이디를 입력하세요: ";
    cin >> id;
    cout << "이름을 입력하세요: ";
    cin >> name;
    cout << "생일을 입력하세요(0000-00-00형식으로 입력): ";
    cin >> birthday;

    while (res->next()) {

        if (res->getString("id") == id) {
            if (res->getString("name") == name) {
                if (res->getString("birthday") == birthday) {
                    cout << "회원님의 비밀번호는 " << res->getString("pw") << " 입니다." << endl;  //이름+id+생일 일치 -> pw 제공 
                    existpw = true;
                    exit(0);
                }
                else {
                    existpw = false;
                }
            }
            else {
                existpw = false;  //이름일치+생일불일치
                break;
            }

        }
        else {
            existpw = false;
        }
    }

    if (existpw == false) {
        cout << "존재하지 않는 회원입니다. 회원가입을 해주세요." << endl;
        exit(0);
    }

}