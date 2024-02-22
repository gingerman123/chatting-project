#include <iostream>
#include <string>
#include <mysql/jdbc.h>
#include "Login.h"

using std::cout;
using std::endl;
using std::string;

const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
const string username = "root"; // 데이터베이스 사용자
const string password = "3432"; // 데이터베이스 접속 비밀번호

//테이블 생성 후 첫번째 회원의 정보를 집어넣는다 


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


        // 데이터베이스 쿼리 실행
        stmt = con->createStatement();
        stmt->execute("DROP TABLE IF EXISTS user"); // DROP
        cout << "Finished dropping table (if existed)" << endl;
        stmt->execute("CREATE TABLE user (id varchar(10) NOT NULL PRIMARY KEY ,pw varchar(20) NOT NULL,name varchar(10) NOT NULL,gender varchar(1) NOT NULL,birthday date NOT NULL,nickname varchar(10) NOT NULL);"); // CREATE
        cout << "Finished creating table" << endl;
        delete stmt;


       //회원1 의 정보 입력

        pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // INSERT

        pstmt->setString(1, "sdd01");
        pstmt->setString(2, "0111");
        pstmt->setString(3, "Kimsu");
        pstmt->setString(4, "M");
        pstmt->setDateTime(5, "2001-11-20");
        pstmt->setString(6, "yoi");

        pstmt->execute();

        cout << "Complete" << endl;
        
        Login();  // 로그인 함수 실행 

         //MySQL Connector/C++ 정리
        delete pstmt;
        delete con;

    


    return 0;
}