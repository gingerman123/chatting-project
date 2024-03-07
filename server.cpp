#pragma comment(lib, "ws2_32.lib") //������� ���̺귯���� ��ũ. ���� ���̺귯�� ����
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



const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "wndud0602!"; // �����ͺ��̽� ���� ��й�ȣ

struct SOCKET_INFO { // ����� ���� ������ ���� Ʋ ����
    SOCKET sck;
    string user;
    int ti;
};

std::vector<SOCKET_INFO> sck_list; // ����� Ŭ���̾�Ʈ ���ϵ��� ������ �迭 ����.
SOCKET_INFO server_sock; // ���� ���Ͽ� ���� ������ ������ ���� ����.
int client_count = 0; // ���� ������ �ִ� Ŭ���̾�Ʈ�� count �� ���� ����.
//string UTF8(const string& input);
void server_init(); // socket �ʱ�ȭ �Լ�. socket(), bind(), listen() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void add_client(int ti); // ���Ͽ� ������ �õ��ϴ� client�� �߰�(accept)�ϴ� �Լ�. client accept() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void send_msg(string msg); // send() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void recv_msg(string user); // recv() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void del_client(int idx); // ���Ͽ� ����Ǿ� �ִ� client�� �����ϴ� �Լ�. closesocket() �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
SOCKET getSocket(string user);
int removeSocket(string user);




int recreate = -1;
int num = 0; // ���ϸ��� �ѹ� �־��ٰž�

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


MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
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

    // �����ͺ��̽� ����
    con->setSchema("chat");

    // db �ѱ� ������ ���� ���� 
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }


    WSADATA wsa;

    // Winsock�� �ʱ�ȭ�ϴ� �Լ�. MAKEWORD(2, 2)�� Winsock�� 2.2 ������ ����ϰڴٴ� �ǹ�.
    // ���࿡ �����ϸ� 0��, �����ϸ� �� �̿��� ���� ��ȯ.
    // 0�� ��ȯ�ߴٴ� ���� Winsock�� ����� �غ� �Ǿ��ٴ� �ǹ�.
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (!code) {
        server_init();

        for (int i = 0; i < MAX_CLIENT; i++) {
            // �ο� �� ��ŭ thread �����ؼ� ������ Ŭ���̾�Ʈ�� ���ÿ� ������ �� �ֵ��� ��.
            th1[i] = std::thread(add_client, i);
        }
        //std::thread th1(add_client); // �̷��� �ϸ� �ϳ��� client�� �޾���...
        std::thread th2(recreateThread);

        while (1) { // ���� �ݺ����� ����Ͽ� ������ ����ؼ� ä�� ���� �� �ִ� ���¸� ����� ��. �ݺ����� ������� ������ �� ���� ���� �� ����.
            string text, msg = "";

            std::getline(cin, text);
            const char* buf = text.c_str();
            msg = server_sock.user + " : " + buf;
            send_msg(msg.c_str());
        }

        for (int i = 0; i < MAX_CLIENT; i++) {
            th1[i].join();
            //join : �ش��ϴ� thread ���� ������ �����ϸ� �����ϴ� �Լ�.
            //join �Լ��� ������ main �Լ��� ���� ����Ǿ thread�� �Ҹ��ϰ� ��.
            //thread �۾��� ���� ������ main �Լ��� ������ �ʵ��� ����.
        }
        //th1.join();
        th2.join();

        closesocket(server_sock.sck);
    }
    else {
        cout << "���α׷� ����. (Error code : " << code << ")";
    }

    WSACleanup();

    return 0;
}

void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Internet�� Stream ������� ���� ����
   // SOCKET_INFO�� ���� ��ü�� socket �Լ� ��ȯ��(��ũ���� ����)
   // ���ͳ� �ּ�ü��, ��������, TCP �������� �� ��. 

    SOCKADDR_IN server_addr = {}; // ���� �ּ� ���� ����
    // ���ͳ� ���� �ּ�ü�� server_addr

    server_addr.sin_family = AF_INET; // ������ Internet Ÿ�� 
    server_addr.sin_port = htons(7777); // ���� ��Ʈ ����
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // �����̱� ������ local �����Ѵ�. 
    //Any�� ���� ȣ��Ʈ�� 127.0.0.1�� ��Ƶ� �ǰ� localhost�� ��Ƶ� �ǰ� ���� �� ����ϰ� �� �� �ֵ�. �װ��� INADDR_ANY�̴�.
    //ip �ּҸ� ������ �� server_addr.sin_addr.s_addr -- ������ ���?

    int b = ::bind(server_sock.sck, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
    // ������ ���� ������ ���Ͽ� ���ε��Ѵ�.
    int l = listen(server_sock.sck , SOMAXCONN); // ������ ��� ���·� ��ٸ���.
    //cout << "b " << b << ", l " << l << endl;

    server_sock.user = "server";

    cout << "Server On" << endl;
}

void add_client(int ti) {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };
    ZeroMemory(&addr, addrsize); // addr�� �޸� ������ 0���� �ʱ�ȭ

    SOCKET_INFO new_client = {};

    cout << "before accept" << endl;
    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    cout << "after accept" << endl;

    string judge;       // �ĺ���
    string id;          // Ŭ���̾�Ʈ id ���� ����
    string pw;          // Ŭ���̾�Ʈ pw ���� ����
    string name;        // Ŭ���̾�Ʈ �̸� ���� ����
    string gender;      // Ŭ���̾�Ʈ ���� ���� ����
    string birth;       // Ŭ���̾�Ʈ ������� ���� ����
    string nickname;    // Ŭ���̾�Ʈ �г��� ���� ����
    string msg;
    string dup;
    string check;       // DB���� ����� ���� ����


    bool login = false; //�α��� �Ǹ� Ż��
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
        string log_msg = string(buf);   //���� �޽��� string Ÿ������ ��ȯ�ؼ� ����
        cout << log_msg<<endl;
        stringstream option_judge(log_msg); //�ĺ��� �����ϱ� ����
        option_judge >> judge;
        cout << judge << endl;
        if (judge == "login") {         //�ĺ��ڰ� login�� ���
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
            // ��Ʈ��ũ ������ ���� UTF-8 ���ڿ� ����
            send(new_client.sck, msg.c_str(), msg.length(), 0);
        }
        else if(judge == "findPW") {        //�ĺ��ڰ� findPW�� ���
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
            // ��Ʈ��ũ ������ ���� UTF-8 ���ڿ� ����
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
    string announce = "msg%[����] " + new_client.user + " ���� �����߽��ϴ�.";
    cout << announce << endl;
    client_count++; // client �� ����.
    cout << "���� : ���� ������ ���� " << client_count << "��" << endl;
    sck_list.push_back(new_client); // client ������ ��� sck_list �迭�� ���ο� client �߰�



    std::thread th(recv_msg, new_client.user);
    // �ٸ� �����κ��� ���� �޽����� ����ؼ� ���� �� �ִ� ���·� ����� �α�.

    send_msg(announce);
    // c_str : string Ÿ���� const chqr* Ÿ������ �ٲ���.
    th.join();
    cout << "th.join()" << endl;
}


void send_msg(string msg) {

    for (int i = 0; i < sck_list.size(); i++) { // ������ �ִ� ��� client���� �޽��� ����
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
            mhour = "���� " + nhour;
        }
        else {
            mhour = "���� " + nhour;
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
        if (recv(sck, buf, MAX_SIZE, 0) > 0) { // ������ �߻����� ������ recv�� ���ŵ� ����Ʈ ���� ��ȯ. 0���� ũ�ٴ� ���� �޽����� �Դٴ� ��.
            string tmp = string(buf);
            string text = tmp.substr(tmp.find(" ")+1);
            msg = "msg%" + user + " : " + text + " " + "[" + ntime + "]";
            send_msg(msg);
            save_msg(driver, con, pstmt, user, text, date, time);

        }
        else { //�׷��� ���� ��� ���忡 ���� ��ȣ�� �����Ͽ� ���� �޽��� ����
            msg = "msg%[����] " + user + " ���� �����߽��ϴ�.";
            cout << msg << endl;
            send_msg(msg.c_str());
            //del_client(idx); // Ŭ���̾�Ʈ ����
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
    sck_list.erase(sck_list.begin() + idx); // �迭���� Ŭ���̾�Ʈ�� �����ϰ� �� ��� index�� �޶����鼭 ��Ÿ�� ���� �߻�....��
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


