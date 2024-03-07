#include "signIn.h"



string id;
string pw;
string name;
string birth;
string nickname;
string gender;
string member[6] = { id, pw, name, gender,birth, nickname };
string str_member[6] = { "아이디","비밀번호","이름","성별","생년월일","별명" };



void create(MySQL_Driver* driver, Connection* con, Statement* stmt) {
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS user;"); // DROP
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE user(id VARCHAR(50) NOT NULL PRIMARY KEY,pw VARCHAR(50) NOT NULL,name VARCHAR(20)NOT NULL,gender VARCHAR(3),birth DATE,nickname VARCHAR(35));");// CREATE
	cout << "Finished creating table" << endl;
	delete stmt;
}	
void signin_t(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt,std::string id_1,std::string pw_1) {
	pstmt = con->prepareStatement("INSERT INTO id(id,pw) VALUES(?,?)"); // id 테이블 insert
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
}	 //서버
void signin(MySQL_Driver* driver, Connection* con, Statement* stmt, PreparedStatement* pstmt) {


	pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user 테이블 insert

	for (int i = 0; i < 6; i++) {		//각 회원정보 입력 받기
		ResultSet* res;
		bool complete = false;
		while (!complete) {		//하나씩 조건 만족하는 지 체크하며 만족할 때까지 입력받기
			i == 4? cout << str_member[i] + " 을 (0000-00-00) 형식으로 입력하세요.\n" :cout << str_member[i] + " 을(를) 입력하세요\n";
			cin >> member[i];

			//ID,PW
			if (i < 2) {	//ID,PW 공통
				bool isInRange = false;			//범위 안에 있는지 Y or N
				if (member[i].size() < 1 || member[i].size() > 15) { //글자수 제한 맞으면 다시 입력 받기
					cout << str_member[i] + " 글자 수를 맞춰주세요.\n";
				}
				else {		//글자수 맞으면 true;
					isInRange = true;
					complete = true;
				}
				// ID
				if (i == 0 && isInRange) {
					bool isDuple = false;		//ID 중복체크 Y or N
					complete = false;

					stmt = con->createStatement();
					res = stmt->executeQuery("SELECT * FROM user");
					int count = 0;
					while (res->next()) {
						if (member[i] == res->getString("id")) {	// 중복이라면 다시 입력 받기
							cout << "중복된 id입니다\n";
							count++;
						}
						else {		// 중복 없다면 true
							isDuple = true;
						}
					}
					delete res;
					delete stmt;


					if (count == 0) {	//글자수랑 중복 다 체크 됐다면 반복 종료
						complete = true;
					}
				}
			}
			//NAME
			else if (i == 2) {	//name일때
				if (member[i].size() < 0 || member[i].size() > 10) { //글자수 제한 맞으면 다시 입력 받기
					cout << str_member[i] + " 글자 수를 맞춰주세요.\n";
					continue;
				}
				else {		//글자수 맞으면 true;
					complete = true;
				}
			}
			//GENDER
			else if (i == 3) {	//gender일때
				if (member[i] == "F"|| member[i] =="M") { //F or M으로만 입력받기
					complete = true;
				}
				else {	//틀리면 다시 입력받기
					cout << " F or M으로만 입력해주세요.\n";
					continue;
				}
			}
			//BIRTH
			else if (i == 4) {
				//현재 날짜 받는 코드
				auto now = std::chrono::system_clock::now();
				auto now_time = std::chrono::system_clock::to_time_t(now);
				std::tm now_tm;
				localtime_s(&now_tm, &now_time);

				int year = now_tm.tm_year + 1900;
				int month = now_tm.tm_mon + 1;
				int day = now_tm.tm_mday;

				if (member[i].size() != 10) {	//10글자 맞는지 체크
					continue;
				}
				//내가 입력한 년,월,일로 저장
				string input_year = member[i].substr(0, 4);
				string input_mon = member[i].substr(5, 2);
				string input_day = member[i].substr(8, 2);
				
				string date = input_year + input_mon + input_day;	//string타입 ex)"20240125"
				int now_date = 10000 * year + 100 * month + day;	//int타입 ex)20240125

				bool isInRange1 = false;
				bool isInRange2 = false;
				bool isDate = false;
				if (member[i].size() == 10) {		//10글자 맞는지 체크
					if (member[i].substr(4, 1) == "-" && member[i].substr(7, 1) == "-") {		//날짜 형식이 맞는지 체크
						isDate = true;
						if (stoi(date) < now_date + 1) {	//현재 날짜보다 이후인지 체크
							isInRange1 = true;
						}

						if (stoi(input_year)> 0) {		//0년 이상인지
							if ( stoi(input_mon)> 0 && stoi(input_mon) < 13) {		//1~12월인지
								if (stoi(input_day) > 0 && stoi(input_day) < 32) {		//1일~31일인지
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
				if (member[i].size() < 0 || member[i].size() > 20) { //글자수 제한 맞으면 다시 입력 받기
					cout << str_member[i] + " 글자 수를 맞춰주세요.\n";
					continue;
				}
				else {		//글자수 맞으면 true;
					complete = true;
				}
			}
		}

		i == 4? pstmt->setDateTime(i+1,member[i]) : pstmt->setString(i + 1, member[i]);		//birth면 datetime으로 나머지는 string으로 입력
	}
	pstmt->execute();
	cout << "회원가입이 완료되었습니다.\n";

}
string check_id(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt,ResultSet* res,const string& id,const string& pw) {
	pstmt = con->prepareStatement("SELECT pw FROM user WHERE id = ?"); // 입력 받은 id가 있는 행의 pw를 선택
	pstmt->setString(1, id);
	res = pstmt->executeQuery();
	string db_pw;
	string result = "N";	//기본적으로 N을 리턴함
	while (res->next()) {	//db_pw 변수에 pw를 저장
		db_pw = res->getString("pw");
	}
	if (db_pw == pw) {		//입력한 pw와 db에서 찾은 pw가 같으면 Y 리턴
		result = "Y";
	}

	return result;
};
string find_pw(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id, const string& birth){
	pstmt = con->prepareStatement("SELECT id,pw FROM user WHERE id = ? and birthday = ?");	// id와 birthday
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
	pstmt = con->prepareStatement("SELECT id,name,birthday FROM user WHERE name = ? and birthday = ?");	// id와 birthday
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
	pstmt = con->prepareStatement("SELECT id,nickname FROM user WHERE id = ?");	// id와 nickname
	pstmt->setString(1, id);
	res = pstmt->executeQuery();
	string nickname;
	while (res->next()) {
		nickname = res->getString("nickname");
	}
	return nickname;
}
string isdup(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, ResultSet* res, const string& id) {
	pstmt = con->prepareStatement("SELECT id FROM user");	// id와 birthday
	res = pstmt->executeQuery();
	string result = "Y";		//겹치는 게 없으면 Y
	string db_id;
	while (res->next()) {
		db_id = res->getString("id");
		if (db_id == id) {
			result = "N";		//겹치는 게 있으면 N
		}
	}

	return result;
}
void reg(MySQL_Driver* driver, Connection* con, PreparedStatement* pstmt, const string& id, const string& pw, const string& name, const string& gender, const string& birthday, const string& nickname) { 
	if (gender == "null") {
		pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,null,?,?)"); // user 테이블에 접근 
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
	pstmt = con->prepareStatement("INSERT INTO chatlog(nickname,msg,date,time) VALUES(?,?,?,?)"); // user 테이블에 접근 
	pstmt->setString(1, nickname);
	pstmt->setString(2, msg);
	pstmt->setString(3, date);
	pstmt->setString(4, time);
	pstmt->execute();

}