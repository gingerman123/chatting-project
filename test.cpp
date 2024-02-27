# include <iostream>
# include <vector>
# include <string>
#include <typeinfo>
#include <iostream>
#include <chrono>
#include <ctime>


using namespace std;

int main() {
	auto now = std::chrono::system_clock::now();
	auto now_time = std::chrono::system_clock::to_time_t(now);
	std::tm now_tm;
	localtime_s(&now_tm, &now_time);

	int year = now_tm.tm_year + 1900;
	int month = now_tm.tm_mon + 1;
	int day = now_tm.tm_mday;

	string m = "1997-01-25";

	//cout << year << " " << month << " " << day;
	//cout << m.size();


	int now_date = 10000 * year + 100 * month + day;
	cout << now_date;
	/*string date = m.substr(0, 4) + m.substr(5, 2) + m.substr(8, 2);
	cout << date;*/
	//cout << m.substr(0, 4)<<endl;
	//cout << m.substr(5, 2)<<endl;
	//cout << m.substr(8, 2)<<endl;
	//cout << m.size() << endl;

	//cout << typeid(m.at(4)).name()<<endl;
	//cout << typeid(m[4]).name() << endl;
	//cout << typeid(stoi(m.substr(0, 4))).name();

	//if (m.substr(7,1) == "-") {
	//	cout << "¸¸¼¼";
	//}

	return 0;
}