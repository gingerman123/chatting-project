#include "signIn.h"



string id;
string pw;
string name;
string birth;
string nickname;
string gender;
string member[6] = { id, pw, name, gender,birth, nickname };
string str_member[6] = { "���̵�","��й�ȣ","�̸�","����","�������","����" };



void create(MySQL_Driver* driver, Connection* con, Statement* stmt) {
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS user;"); // DROP
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE user(id VARCHAR(50) NOT NULL PRIMARY KEY,pw VARCHAR(50) NOT NULL,name VARCHAR(20)NOT NULL,gender VARCHAR(3),birth DATE,nickname VARCHAR(35));");// CREATE
	cout << "Finished creating table" << endl;
	delete stmt;
}	
void signin_t(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt,std::string id_1,std::string pw_1) {
	pstmt = con->prepareStatement("INSERT INTO id(id,pw) VALUES(?,?)"); // id ���̺� insert
	pstmt->setString(1,id_1);
	pstmt->setString(2,pw_1);
	pstmt->execute();
}
void create_t(MySQL_Driver* driver, Connection* con, Statement* stmt,const string& table_name) {
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS " + table_name); // DROP
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE "+ table_name + "(id VARCHAR(15) NOT NULL PRIMARY KEY,pw VARCHAR(15) NOT NULL);");// CREATE
	cout << "Finished creating table" << endl;
		
	delete stmt;
}	 //����
void signin(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt) {


	pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user ���̺� insert

	for (int i = 0; i < 6; i++) {		//�� ȸ������ �Է� �ޱ�
		ResultSet* res;
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
string check_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt,ResultSet* res,const string& id,const string& pw) {
	pstmt = con->prepareStatement("SELECT pw FROM user WHERE id = ?"); // �Է� ���� id�� �ִ� ���� pw�� ����
	pstmt->setString(1, id);
	res = pstmt->executeQuery();
	string db_pw;
	string result = "N";	//�⺻������ N�� ������
	while (res->next()) {	//db_pw ������ pw�� ����
		db_pw = res->getString("pw");
	}
	if (db_pw == pw) {		//�Է��� pw�� db���� ã�� pw�� ������ Y ����
		result = "Y";
	}

	return result;
};
string find_pw(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id, const string& birth){
	pstmt = con->prepareStatement("SELECT id,pw FROM user WHERE id = ? and birthday = ?");	// id�� birthday
	pstmt->setString(1, id);
	pstmt->setString(2, birth);
	res = pstmt->executeQuery();
	string result = "N";
	string pw = "";
	string db_id;
	string db_pw;
	while (res->next()) {
		db_id = res->getString("id");
		db_pw = res->getString("pw");
	}

	if (db_id == id) {
		pw = db_pw;
		result = "Y";
	}
	result += " " + pw;


	return result;
};
string find_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& name, const string& birth) {
	pstmt = con->prepareStatement("SELECT id,name,birthday FROM user WHERE name = ? and birthday = ?");	// id�� birthday
	pstmt->setString(1, name);
	pstmt->setString(2, birth);
	res = pstmt->executeQuery();
	string result = "N";
	string id = "";
	string db_name;
	string db_id;
	string db_birth;
	while (res->next()) {
		db_id = res->getString("id");
		db_name = res->getString("name");
		db_birth = res->getString("birthday");
	}

	if (db_name == name&& db_birth == birth) {
		id = db_id;
		result = "Y";
	}
	result += " " + id;
	return result;

}
string find_nickname(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id) {
	pstmt = con->prepareStatement("SELECT id,nickname FROM user WHERE id = ?");	// id�� nickname
	pstmt->setString(1, id);
	res = pstmt->executeQuery();
	string nickname;
	while (res->next()) {
		nickname = res->getString("nickname");
	}
	return nickname;
}
string isdup(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id) {
	pstmt = con->prepareStatement("SELECT id FROM user");	// id�� birthday
	res = pstmt->executeQuery();
	string result = "Y";		//��ġ�� �� ������ Y
	string db_id;
	while (res->next()) {
		db_id = res->getString("id");
		if (db_id == id) {
			result = "N";		//��ġ�� �� ������ N
		}
	}

	return result;
}
void reg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, const string& id, const string& pw, const string& name, const string& gender, const string& birthday, const string& nickname) { 
	if (gender == "null") {
		pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,null,?,?)"); // user ���̺� ���� 
		pstmt->setString(1, id);
		pstmt->setString(2, pw);
		pstmt->setString(3, name);
		pstmt->setString(4, birthday);
		pstmt->setString(5, nickname);
	}
	else {
		pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)");
		pstmt->setString(1, id);
		pstmt->setString(2, pw);
		pstmt->setString(3, name);
		pstmt->setString(4, gender);
		pstmt->setString(5, birthday);
		pstmt->setString(6, nickname);
	}
	pstmt->execute();


}
void save_msg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, const string& nickname, const string& msg, const string& date, const string& time)
{
	pstmt = con->prepareStatement("INSERT INTO chatlog(nickname,msg,date,time) VALUES(?,?,?,?)"); // user ���̺� ���� 
	pstmt->setString(1, nickname);
	pstmt->setString(2, msg);
	pstmt->setString(3, date);
	pstmt->setString(4, time);
	pstmt->execute();

}