#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	cin.get();
	cin.get();
	string str;
	for (int i = 0; i < n; i++)
	{
		cin >> str;
		for (size_t len = 1; len <= str.size(); len++)
		{
			bool b = true;
			if (str.size() % len == 0){
				size_t cnt = str.size() / len;
				string strTmp(str.substr(0, len));
				for (size_t k = 1; k < cnt; k++)
				{
					strTmp += str.substr(0, len);
					if (strTmp != str.substr(0, strTmp.size())){
						b = false;
						break;
					}
				}
				if (b){
					cout << len << endl;
					break;
				}
			}
		}
		if (i != n - 1) cout << endl;
	}
	return 0;
}
/*
1

HoHoHo
*/
