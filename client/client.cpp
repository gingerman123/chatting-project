#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock ������� include. WSADATA �������.
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>

#define MAX_SIZE 1024

using std::cout;
using std::cin;
using std::endl;
using std::string;

SOCKET client_sock;
string my_nick;
string id;
string pw;
string name;
string birth;
string nickname;
string gender;
string member[6] = { id, pw, name, gender,birth, nickname };
string str_member[6] = { "���̵�","��й�ȣ","�̸�","����","�������","����" };


void SignIn(){
    cout << "id�� �Է��ϼ���";
    cin >> id;
    send(client_sock, id.c_str(), id.length(), 0);
    cout << "pw�� �Է��ϼ���";
    cin >> pw;
    send(client_sock, pw.c_str(), pw.length(), 0);
}

int chat_recv() {
    char buf[MAX_SIZE] = { };
    string msg;

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            std::stringstream ss(msg);  // ���ڿ��� ��Ʈ��ȭ
            string user;
            ss >> user; // ��Ʈ���� ����, ���ڿ��� ���� �и��� ������ �Ҵ�. ���� ����� �̸��� user�� �����.
            if (user != my_nick) cout << buf << endl; // ���� ���� �� �ƴ� ��쿡�� ����ϵ���.
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}




int main() {
    WSADATA wsa;

    // Winsock�� �ʱ�ȭ�ϴ� �Լ�. MAKEWORD(2, 2)�� Winsock�� 2.2 ������ ����ϰڴٴ� �ǹ�.
    // ���࿡ �����ϸ� 0��, �����ϸ� �� �̿��� ���� ��ȯ.
    // 0�� ��ȯ�ߴٴ� ���� Winsock�� ����� �غ� �Ǿ��ٴ� �ǹ�.
    int code = WSAStartup(MAKEWORD(2, 2), &wsa);

    if (!code) {
        cout << "����� �г��� �Է� >> ";
        cin >> my_nick;

        client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); // 

        // ������ ���� ���� ���� �κ�
        SOCKADDR_IN client_addr = {};
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(7777);
        InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);
        while (1) {
            if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) { // ���� ������ ������ �ش��ϴ� server�� ����!
                cout << "Server Connect" << endl;
                send(client_sock, my_nick.c_str(), my_nick.length(), 0); // ���ῡ �����ϸ� client �� �Է��� �г����� ������ ����
                SignIn();
                break; 
            }
            cout << "Connecting..." << endl;
        }

        std::thread th2(chat_recv);

        while (1) {
            string text;
            std::getline(cin, text);
            const char* buffer = text.c_str(); // string���� char* Ÿ������ ��ȯ
            send(client_sock, buffer, strlen(buffer), 0);
        }
        th2.join();
        closesocket(client_sock);
    }

    WSACleanup();
    return 0;
}