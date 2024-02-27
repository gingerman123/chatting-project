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
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS user"); // DROP
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE user(id VARCHAR(15) NOT NULL PRIMARY KEY,pw VARCHAR(15) NOT NULL,name VARCHAR(15) NOT NULL,gender VARCHAR(1),birthday DATE NOT NULL,nickname VARCHAR(20) NOT NULL);");// CREATE
	cout << "Finished creating table" << endl;

	delete stmt;
}	 //����

void signin(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::PreparedStatement* pstmt) {


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
				//���� ��¥ �޴� �ڵ�
				auto now = std::chrono::system_clock::now();
				auto now_time = std::chrono::system_clock::to_time_t(now);
				std::tm now_tm;
				localtime_s(&now_tm, &now_time);

				int year = now_tm.tm_year + 1900;
				int month = now_tm.tm_mon + 1;
				int day = now_tm.tm_mday;

				if (member[i].size() != 10) {	//10���� �´��� üũ
					continue;
				}
				//���� �Է��� ��,��,�Ϸ� ����
				string input_year = member[i].substr(0, 4);
				string input_mon = member[i].substr(5, 2);
				string input_day = member[i].substr(8, 2);
				
				string date = input_year + input_mon + input_day;	//stringŸ�� ex)"20240125"
				int now_date = 10000 * year + 100 * month + day;	//intŸ�� ex)20240125

				bool isInRange1 = false;
				bool isInRange2 = false;
				bool isDate = false;
				if (member[i].size() == 10) {		//10���� �´��� üũ
					if (member[i].substr(4, 1) == "-" && member[i].substr(7, 1) == "-") {		//��¥ ������ �´��� üũ
						isDate = true;
						if (stoi(date) < now_date + 1) {	//���� ��¥���� �������� üũ
							isInRange1 = true;
						}

						if (stoi(input_year)> 0) {		//0�� �̻�����
							if ( stoi(input_mon)> 0 && stoi(input_mon) < 13) {		//1~12������
								if (stoi(input_day) > 0 && stoi(input_day) < 32) {		//1��~31������
									isInRange2 = true;
								}
							}
						
						}
					}
				}

				if (isInRange1 && isInRange2 && isDate) {
					complete = true;
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
		}

		i == 4? pstmt->setDateTime(i+1,member[i]) : pstmt->setString(i + 1, member[i]);		//birth�� datetime���� �������� string���� �Է�
	}
	pstmt->execute();
	cout << "ȸ�������� �Ϸ�Ǿ����ϴ�.\n";

}
