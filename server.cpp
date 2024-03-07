#pragma comment(lib, "ws2_32.lib") //명시적인 라이브러리의 링크. 윈속 라이브러리 참조
#pragma once
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>
#include <stdio.h>
#include <ctime>
#include "signin.h"


#define MAX_SIZE 1024
#define MAX_CLIENT 5

using namespace std;



const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
const string username = "root"; // 데이터베이스 사용자
const string password = "wndud0602!"; // 데이터베이스 접속 비밀번호

struct SOCKET_INFO { // 연결된 소켓 정보에 대한 틀 생성
    SOCKET sck;
    string user;
    int ti;
};

std::vector<SOCKET_INFO> sck_list; // 연결된 클라이언트 소켓들을 저장할 배열 선언.
SOCKET_INFO server_sock; // 서버 소켓에 대한 정보를 저장할 변수 선언.
int client_count = 0; // 현재 접속해 있는 클라이언트를 count 할 변수 선언.
//string UTF8(const string& input);
void server_init(); // socket 초기화 함수. socket(), bind(), listen() 함수 실행됨. 자세한 내용은 함수 구현부에서 확인.
void add_client(int ti); // 소켓에 연결을 시도하는 client를 추가(accept)하는 함수. client accept() 함수 실행됨. 자세한 내용은 함수 구현부에서 확인.
void send_msg(string msg); // send() 함수 실행됨. 자세한 내용은 함수 구현부에서 확인.
void recv_msg(string user); // recv() 함수 실행됨. 자세한 내용은 함수 구현부에서 확인.
void del_client(int idx); // 소켓에 연결되어 있는 client를 제거하는 함수. closesocket() 실행됨. 자세한 내용은 함수 구현부에서 확인.
SOCKET getSocket(string user);
int removeSocket(string user);




int recreate = -1;
int num = 0; // 소켓마다 넘버 넣어줄거야

//void makesoc_id() {
//    for (int i = 0; i < 1000, i++;) {
//        string end_num = to_string(i);
//        (4 - end_num.size());
//    }
//
//}

std::thread th1[MAX_CLIENT];

void recreateThread() {
    while (1) {
        //cout << "recreate " << recreate << endl;
        if (recreate > -1) {
            //cout << "th1.join() " << recreate << endl;
            th1[recreate].join();
            //cout << "join " << recreate << endl;
            th1[recreate] = std::thread(add_client, recreate);
            recreate = -1;
        }
        if (recreate == -2) {
            return;
        }
        Sleep(1000);
    }
}


MySQL_Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
Connection* con;
Statement* stmt;
PreparedStatement* pstmt;
ResultSet* res;


int main() {


    try {
        driver = get_mysql_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }

    // 데이터베이스 선택
    con->setSchema("chat");

    // db 한글 저장을 위한 셋팅 
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }


    WSADATA wsa;

    // Winsock를 초기화하는 함수. MAKEWORD(2, 2)는 Winsock의 2.2 버전을 사용하겠다는 의미.
    // 실행에 성공하면 0을, 실패하면 그 이외의 값을 반환.
    // 0을 반환했다는 것은 Winsock을 사용할 준비가 되었다는 의미.
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (!code) {
        server_init();

        for (int i = 0; i < MAX_CLIENT; i++) {
            // 인원 수 만큼 thread 생성해서 각각의 클라이언트가 동시에 소통할 수 있도록 함.
            th1[i] = std::thread(add_client, i);
        }
        //std::thread th1(add_client); // 이렇게 하면 하나의 client만 받아짐...
        std::thread th2(recreateThread);

        while (1) { // 무한 반복문을 사용하여 서버가 계속해서 채팅 보낼 수 있는 상태를 만들어 줌. 반복문을 사용하지 않으면 한 번만 보낼 수 있음.
            string text, msg = "";

            std::getline(cin, text);
            const char* buf = text.c_str();
            msg = server_sock.user + " : " + buf;
            send_msg(msg.c_str());
        }

        for (int i = 0; i < MAX_CLIENT; i++) {
            th1[i].join();
            //join : 해당하는 thread 들이 실행을 종료하면 리턴하는 함수.
            //join 함수가 없으면 main 함수가 먼저 종료되어서 thread가 소멸하게 됨.
            //thread 작업이 끝날 때까지 main 함수가 끝나지 않도록 해줌.
        }
        //th1.join();
        th2.join();

        closesocket(server_sock.sck);
    }
    else {
        cout << "프로그램 종료. (Error code : " << code << ")";
    }

    WSACleanup();

    return 0;
}

void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Internet의 Stream 방식으로 소켓 생성
   // SOCKET_INFO의 소켓 객체에 socket 함수 반환값(디스크립터 저장)
   // 인터넷 주소체계, 연결지향, TCP 프로토콜 쓸 것. 

    SOCKADDR_IN server_addr = {}; // 소켓 주소 설정 변수
    // 인터넷 소켓 주소체계 server_addr

    server_addr.sin_family = AF_INET; // 소켓은 Internet 타입 
    server_addr.sin_port = htons(7777); // 서버 포트 설정
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // 서버이기 때문에 local 설정한다. 
    //Any인 경우는 호스트를 127.0.0.1로 잡아도 되고 localhost로 잡아도 되고 양쪽 다 허용하게 할 수 있따. 그것이 INADDR_ANY이다.
    //ip 주소를 저장할 땐 server_addr.sin_addr.s_addr -- 정해진 모양?

    int b = ::bind(server_sock.sck, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
    // 설정된 소켓 정보를 소켓에 바인딩한다.
    int l = listen(server_sock.sck , SOMAXCONN); // 소켓을 대기 상태로 기다린다.
    //cout << "b " << b << ", l " << l << endl;

    server_sock.user = "server";

    cout << "Server On" << endl;
}

void add_client(int ti) {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };
    ZeroMemory(&addr, addrsize); // addr의 메모리 영역을 0으로 초기화

    SOCKET_INFO new_client = {};

    cout << "before accept" << endl;
    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    cout << "after accept" << endl;

    string judge;       // 식별자
    string id;          // 클라이언트 id 받을 변수
    string pw;          // 클라이언트 pw 받을 변수
    string name;        // 클라이언트 이름 받을 변수
    string gender;      // 클라이언트 성별 받을 변수
    string birth;       // 클라이언트 생년월일 받을 변수
    string nickname;    // 클라이언트 닉네임 받을 변수
    string msg;
    string dup;
    string check;       // DB에서 결과를 받을 변수


    bool login = false; //로그인 되면 탈출
    while (!login) {
        memset(buf, 0, sizeof(buf));
        recv(new_client.sck, buf, MAX_SIZE, 0);
        judge = "";
        id = "";
        pw = "";
        name = "";
        gender = "";
        birth = "";
        nickname = "";
        check = "";
        msg = "";
        dup = "";
        string log_msg = string(buf);   //받은 메시지 string 타입으로 변환해서 저장
        cout << log_msg<<endl;
        stringstream option_judge(log_msg); //식별자 구분하기 위해
        option_judge >> judge;
        cout << judge << endl;
        if (judge == "login") {         //식별자가 login인 경우
            stringstream idpw(log_msg);
            idpw >> judge >> id >> pw;
            check = check_id(driver, con, pstmt, res, id, pw);
            if (check == "Y") {
                msg = "Ylogin";
                nickname = find_nickname(driver, con, pstmt, res, id);
                new_client.user = nickname;
                login = true;
                memset(buf, 0, sizeof(buf));
            }
            else {
                msg = "Nlogin";
            }
            // 네트워크 소켓을 통해 UTF-8 문자열 전송
            send(new_client.sck, msg.c_str(), msg.length(), 0);
        }
        else if(judge == "findPW") {        //식별자가 findPW인 경우
            stringstream idbirth(log_msg); 
            idbirth >> judge >> id >> birth;
            string tmp = find_pw(driver, con, pstmt, res, id, birth);

            check = tmp.substr(0,1);

            if (tmp.size() > 1) {
                pw = tmp.substr(2);
            }
            if (check == "Y") {
                msg = "Ypw " + pw;
            }
            else {
                msg = "Npw Npw" ;
            }
            send(new_client.sck, msg.c_str(), msg.length(), 0);
        }
        else if (judge == "findID") {
            stringstream namebirth(log_msg);
            namebirth >> judge>> name >> birth;
            string tmp = find_id(driver, con, pstmt, res, name, birth);

            check = tmp.substr(0, 1);
            if (tmp.size() > 1) {
                id = tmp.substr(2);
            }
            if (check == "Y") {
                msg = "Yid " + id;
            }
            else {
                msg = "Nid Nid";
            }
            send(new_client.sck, msg.c_str(), msg.length(), 0);
        }
        else if (judge =="Dup"){
            stringstream Dupid(log_msg);
            Dupid >> dup >> id;
            
            check = isdup(driver, con, pstmt, res, id);

            if (check == "Y") {
                msg = "Ndup";
            }
            else {
                msg = "Ydup";
            }
            // 네트워크 소켓을 통해 UTF-8 문자열 전송
            send(new_client.sck, msg.c_str(), msg.length(), 0);
        }
        else if (judge == "reg") {
            stringstream regis(log_msg);
            regis >> judge >> id >> pw >> name >> gender >> birth >> nickname;
            cout << id << pw << name << gender << birth << nickname << endl;
            reg(driver,con,pstmt,id,pw,name,gender,birth,nickname);
        }
    }
    //else if (judge == "") {}
    string announce = "msg%[공지] " + new_client.user + " 님이 입장했습니다.";
    cout << announce << endl;
    client_count++; // client 수 증가.
    cout << "공지 : 현재 접속자 수는 " << client_count << "명" << endl;
    sck_list.push_back(new_client); // client 정보를 답는 sck_list 배열에 새로운 client 추가



    std::thread th(recv_msg, new_client.user);
    // 다른 사람들로부터 오는 메시지를 계속해서 받을 수 있는 상태로 만들어 두기.

    send_msg(announce);
    // c_str : string 타입을 const chqr* 타입으로 바꿔줌.
    th.join();
    cout << "th.join()" << endl;
}


void send_msg(string msg) {

    for (int i = 0; i < sck_list.size(); i++) { // 접속해 있는 모든 client에게 메시지 전송
        send(sck_list[i].sck, msg.c_str(), msg.length(), 0);
    }
}

void recv_msg(string user) {
    char buf[MAX_SIZE] = { };


    SOCKET sck = getSocket(user);
    //cout << sck_list[idx].user << endl;

    while (1) {
        time_t timer = time(NULL);
        struct tm t;
        localtime_s(&t, &timer);
        int tmyear = t.tm_year + 1900;
        int tmmonth = t.tm_mon + 1;
        int tmday = t.tm_mday;
        int tmhour = t.tm_hour;
        int tmmin = t.tm_min;
        int tmsec = t.tm_sec;

        string year = to_string(tmyear);
        string mon = to_string(tmmonth);
        string day = to_string(tmday);
        string hour = to_string(tmhour);
        string nhour = "";
        string mhour = "";
        string min = to_string(tmmin);
        string sec = to_string(tmsec);
        
        if (tmhour < 12) {
            nhour = to_string(tmhour);
        }
        else {
            nhour = to_string(tmhour - 12);
        }

        if (nhour.size() < 2) {
            nhour = "0" + nhour;
        }


        if (tmhour < 12) {
            mhour = "오전 " + nhour;
        }
        else {
            mhour = "오후 " + nhour;
        }
        if (hour.size() < 2) {
            hour = "0" + hour;
        }
        if (min.size() < 2) {
            min = "0" + min;
        }
        if (sec.size() < 2) {
            sec = "0" + sec;
        }

        if (hour.size() < 2) {
            hour = "0" + hour;
        }
        if (min.size() < 2) {
            min = "0" + min;
        }
        if (sec.size() < 2) {
            sec = "0" + sec;
        }

        if (mon.size() < 2) {
            mon = "0" + mon;
        }

        if (day.size() < 2) {
            day = "0" + day;
        }

        
        string date = year + "-" + mon + "-" + day;
        string time = hour + ":" + min + ":" + sec;
        string ntime = mhour + ":" + min;

        string msg = "";
        string text = "";
        ZeroMemory(&buf, MAX_SIZE);
        cout << "recv" << endl;
        memset(buf, 0, sizeof(buf));
        if (recv(sck, buf, MAX_SIZE, 0) > 0) { // 오류가 발생하지 않으면 recv는 수신된 바이트 수를 반환. 0보다 크다는 것은 메시지가 왔다는 것.
            string tmp = string(buf);
            string text = tmp.substr(tmp.find(" ")+1);
            msg = "msg%" + user + " : " + text + " " + "[" + ntime + "]";
            send_msg(msg);
            save_msg(driver, con, pstmt, user, text, date, time);

        }
        else { //그렇지 않을 경우 퇴장에 대한 신호로 생각하여 퇴장 메시지 전송
            msg = "msg%[공지] " + user + " 님이 퇴장했습니다.";
            cout << msg << endl;
            send_msg(msg.c_str());
            //del_client(idx); // 클라이언트 삭제
            int remove = removeSocket(user);
            cout << "remove " << remove << endl;
            if (remove > -1) {
                recreate = remove;
                cout << "set recreate " << recreate << endl;
            }
            return;
        }
    }
    cout << "recv_msg out" << endl;
}

void del_client(int idx) {
    closesocket(sck_list[idx].sck);
    sck_list.erase(sck_list.begin() + idx); // 배열에서 클라이언트를 삭제하게 될 경우 index가 달라지면서 런타임 오류 발생....ㅎ
    client_count--;
}

SOCKET getSocket(string user) {
    for (int i = 0; i < sck_list.size(); i++) {
        if (sck_list[i].user == user) {
            return sck_list[i].sck;
        }
    }
    return -1;
}

int removeSocket(string user) {
    int ti;
    for (int i = 0; i < sck_list.size(); i++) {
        if (sck_list[i].user == user) {
            ti = sck_list[i].ti;
            del_client(i);
            return ti;
        }
    }
    return -1;
}


