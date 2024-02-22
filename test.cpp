# include <iostream>
# include <vector>
# include <string>
#include <typeinfo>

using namespace std;

int main() {

	string m = "1997-01-25";

	cout << m.substr(0, 4)<<endl;
	cout << m.substr(5, 2)<<endl;
	cout << m.substr(8, 2)<<endl;
	cout << m.size() << endl;

	cout << typeid(m.at(4)).name()<<endl;
	cout << typeid(m[4]).name() << endl;
	

	if (m.substr(7,1) == "-") {
		cout << "¸¸¼¼";
	}

	return 0;
}