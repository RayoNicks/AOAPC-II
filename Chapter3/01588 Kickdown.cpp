#include <iostream>
#include <string>

using namespace std;

size_t getLen(const string &strDown, const string &strUp)
{
	size_t offset = 0;
	for (; offset < strDown.size(); offset++)
	{
		size_t j = 0;
		for (; j < strUp.size(); j++)
		{
			if (offset + j >= strDown.size()){
				return offset + strUp.size();
			}
			if(strDown[offset + j] - '0' + strUp[j] - '0' > 3) break;
		}
		if (j == strUp.size()){
			return strDown.size();
		}
	}
	return strDown.size() + strUp.size();
}

int main()
{
	string strDown, strUp;
	size_t len1, len2;
	while (cin >> strDown >> strUp){
		len1 = getLen(strDown, strUp);
		len2 = getLen(strUp, strDown);
		if (len1 <= len2) cout << len1 << endl;
		else cout << len2 << endl;
	}
	return 0;
}
/*
2112112112
2212112
12121212
21212121
2211221122
21212
*/
