#include "signIn.h"


using namespace std;


string id;
string pw;
string name;
string birth;
string nickname;
string gender;
string member[6] = { id, pw, name, gender,birth, nickname };
string str_member[6] = { "아이디","비밀번호","이름","성별","생년월일","별명" };







void create(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt) {
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS user"); // DROP
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE user(id VARCHAR(15) NOT NULL PRIMARY KEY,pw VARCHAR(15) NOT NULL,name VARCHAR(15) ,gender VARCHAR(1) ,birthday DATE,nickname VARCHAR(20));");// CREATE
	//stmt->execute("CREATE TABLE user (id varchar(10) NOT NULL PRIMARY KEY ,pw varchar(20) NOT NULL,name varchar(10) NOT NULL,gender varchar(1) NOT NULL,birthday date NOT NULL,nickname varchar(10) NOT NULL);");
	cout << "Finished creating table" << endl;

	delete stmt;
}

void signin(sql::mysql::MySQL_Driver* driver, sql::Connection* con, sql::Statement* stmt, sql::PreparedStatement* pstmt) {


	pstmt = con->prepareStatement("INSERT INTO user(id,pw,name,gender,birthday,nickname) VALUES(?,?,?,?,?,?)"); // user 테이블 insert

	for (int i = 0; i < 6; i++) {		//각 회원정보 입력 받기
		sql::ResultSet* res;
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
