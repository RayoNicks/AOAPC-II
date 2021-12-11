#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str("`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./");
	string strLine;
	string::size_type pos;
	while (getline(cin, strLine)){
		for (auto c : strLine){
			pos = str.find(c);
			if (pos != string::npos){
				cout << str[pos - 1];
			}
			else cout << c;
		}
		cout << endl;
	}
	return 0;
}
