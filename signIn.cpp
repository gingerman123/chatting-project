#include "signIn.h"

using namespace std;


string id;
string pw;
string name;
string birth;
string nickname;
string gender;
string member[6] = { id, pw, name, gender,birth, nickname };
string str_member[6] = { "���̵�","��й�ȣ","�̸�","����","�������","����" };




void create(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt) {
	//// MySQL Connector/C++ �ʱ�ȭ
	//sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
	//sql::Connection* con;
	//sql::Statement* stmt;
	// �����ͺ��̽� ���� ����
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS user"); // DROP
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE user(id VARCHAR(15) NOT NULL PRIMARY KEY,pw VARCHAR(15) NOT NULL,name VARCHAR(15) ,gender VARCHAR(1) ,birthday DATE,nickname VARCHAR(20));");// CREATE
	//stmt->execute("CREATE TABLE user (id varchar(10) NOT NULL PRIMARY KEY ,pw varchar(20) NOT NULL,name varchar(10) NOT NULL,gender varchar(1) NOT NULL,birthday date NOT NULL,nickname varchar(10) NOT NULL);");
	cout << "Finished creating table" << endl;

	delete stmt;
}

void signin(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::PreparedStatement* pstmt) {

	//// MySQL Connector/C++ �ʱ�ȭ
	//sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ ��
	//sql::Connection* con;
	//sql::Statement* stmt;
	//sql::PreparedStatement* pstmt;

	//try {
	//	driver = sql::mysql::get_mysql_driver_instance();
	//	con = driver->connect(server, username, password);
	//}
	//catch (sql::SQLException& e) {
	//	cout << "Could not connect to server. Error message: " << e.what() << endl;
	//	exit(1);
	//}


	//// �����ͺ��̽� ����
	//con->setSchema("chat");

	//// db �ѱ� ������ ���� ���� 
	//stmt = con->createStatement();
	//stmt->execute("set names euckr");
	//if (stmt) { delete stmt; stmt = nullptr; }
	pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user ���̺� insert

	for (int i = 0; i < 6; i++) {		//�� ȸ������ �Է� �ޱ�
		sql::ResultSet* res;
		bool complete = false;
		while (!complete) {		//�ϳ��� ���� �����ϴ� �� üũ�ϸ� ������ ������ �Է¹ޱ�
			i == 4? cout << str_member[i] + " �� (0000-00-00) �������� �Է��ϼ���.\n" :cout << str_member[i] + " ��(��) �Է��ϼ���\n";
			cin >> member[i];

			//ID,PW
			if (i < 2) {	//ID,PW ����
				bool isInRange = false;			//���� �ȿ� �ִ��� Y or N
				if (member[i].size() < 1 || member[i].size() > 15) { //���ڼ� ���� ������ �ٽ� �Է� �ޱ�
					cout << str_member[i] + " ���� ���� �����ּ���.\n";
				}
				else {		//���ڼ� ������ true;
					isInRange = true;
					complete = true;
				}
				// ID
				if (i == 0 && isInRange) {
					bool isDuple = false;		//ID �ߺ�üũ Y or N
					complete = false;

					stmt = con->createStatement();
					res = stmt->executeQuery("SELECT * FROM user");
					int count = 0;
					while (res->next()) {
						if (member[i] == res->getString("id")) {	// �ߺ��̶�� �ٽ� �Է� �ޱ�
							cout << "�ߺ��� id�Դϴ�\n";
							count++;
						}
						else {		// �ߺ� ���ٸ� true
							isDuple = true;
						}
					}
					delete res;
					delete stmt;


					if (count == 0) {	//���ڼ��� �ߺ� �� üũ �ƴٸ� �ݺ� ����
						complete = true;
					}
				}
			}
			//NAME
			else if (i == 2) {	//name�϶�
				if (member[i].size() < 0 || member[i].size() > 10) { //���ڼ� ���� ������ �ٽ� �Է� �ޱ�
					cout << str_member[i] + " ���� ���� �����ּ���.\n";
					continue;
				}
				else {		//���ڼ� ������ true;
					complete = true;
				}
			}
			//GENDER
			else if (i == 3) {	//gender�϶�
				if (member[i] == "F"|| member[i] =="M") { //F or M���θ� �Է¹ޱ�
					complete = true;
				}
				else {	//Ʋ���� �ٽ� �Է¹ޱ�
					cout << " F or M���θ� �Է����ּ���.\n";
					continue;
				}
			}
			//BIRTH
			else if (i == 4) {
				if (birth.substr(4,1) == "-" || birth.substr(7,1) == "-") {		//��¥ ������ �´��� üũ
					if (birth.substr(0,4) == "1") {}
				
				
				}
			}
			//NICKNAME
			else {
				if (member[i].size() < 0 || member[i].size() > 20) { //���ڼ� ���� ������ �ٽ� �Է� �ޱ�
					cout << str_member[i] + " ���� ���� �����ּ���.\n";
					continue;
				}
				else {		//���ڼ� ������ true;
					complete = true;
				}
			}
			//i == 3 ? pstmt->setDateTime(i + 1, member[i]);
		}

		i == 4? pstmt->setDateTime(i+1,member[i]) : pstmt->setString(i + 1, member[i]);		//birth�� datetime���� �������� string���� �Է�
	}
	pstmt->execute();
	cout << "ȸ�������� �Ϸ�Ǿ����ϴ�.\n";

}
