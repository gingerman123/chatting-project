#pragma comment(lib, "ws2_32.lib") //������� ���̺귯���� ��ũ. ���� ���̺귯�� ����
#pragma once
#include <WinSock2.h>
#include <string>
#include <iostream>
#include <thread>
#include <vector>
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

void server_init(); // socket �ʱ�ȭ �Լ�. socket(), bind(), listen() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void add_client(int ti); // ���Ͽ� ������ �õ��ϴ� client�� �߰�(accept)�ϴ� �Լ�. client accept() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void send_msg(const char* msg); // send() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void recv_msg(string user); // recv() �Լ� �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
void del_client(int idx); // ���Ͽ� ����Ǿ� �ִ� client�� �����ϴ� �Լ�. closesocket() �����. �ڼ��� ������ �Լ� �����ο��� Ȯ��.
SOCKET getSocket(string user);
int removeSocket(string user);

int recreate = -1;
std::thread th1[MAX_CLIENT];

void recreateThread() {
    while (1) {
        cout << "recreate " << recreate << endl;
        if (recreate > -1) {
            cout << "th1.join() " << recreate << endl;
            th1[recreate].join();
            cout << "join " << recreate << endl;
            th1[recreate] = std::thread(add_client, recreate);
            recreate = -1;
        }
        if (recreate == -2) {
            return;
        }
        Sleep(1000);
    }
}

//void sql() {
//   
//}


int main() {
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

    create(driver, con, stmt);
    pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user ���̺� insert
 
    


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
    cout << "b " << b << ", l " << l << endl;

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
    recv(new_client.sck, buf, MAX_SIZE, 0);
    // Winsock2�� recv �Լ�. client�� ���� �г����� ����.
    new_client.user = string(buf);
    new_client.ti = ti;

    recv(new_client.sck, buf, MAX_SIZE, 0);
    string id = string(buf);

    string msg = "[����] " + new_client.user + " ���� �����߽��ϴ�.";
    cout << msg << endl;

    sck_list.push_back(new_client); // client ������ ��� sck_list �迭�� ���ο� client �߰�

    std::thread th(recv_msg, new_client.user);
    // �ٸ� �����κ��� ���� �޽����� ����ؼ� ���� �� �ִ� ���·� ����� �α�.

    client_count++; // client �� ����.
    cout << "���� : ���� ������ ���� " << client_count << "��" << endl;

    send_msg(msg.c_str());
    // c_str : string Ÿ���� const chqr* Ÿ������ �ٲ���.

    th.join();
    cout << "th.join()" << endl;
}

void send_msg(const char* msg) {
    for (int i = 0; i < sck_list.size(); i++) { // ������ �ִ� ��� client���� �޽��� ����
        send(sck_list[i].sck, msg, MAX_SIZE, 0);
    }
}

void recv_msg(string user) {
    char buf[MAX_SIZE] = { };
    string msg = "";

    SOCKET sck = getSocket(user);
    //cout << sck_list[idx].user << endl;

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        cout << "recv" << endl;
        if (recv(sck, buf, MAX_SIZE, 0) > 0) { // ������ �߻����� ������ recv�� ���ŵ� ����Ʈ ���� ��ȯ. 0���� ũ�ٴ� ���� �޽����� �Դٴ� ��.
            msg = user + " : " + buf;
            cout << msg << endl;
            send_msg(msg.c_str());
        }
        else { //�׷��� ���� ��� ���忡 ���� ��ȣ�� �����Ͽ� ���� �޽��� ����
            msg = "[����] " + user + " ���� �����߽��ϴ�.";
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