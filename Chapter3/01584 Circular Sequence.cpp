#include <iostream>
#include <string>

using namespace std;

void smallest(const string &strDNA)
{
	size_t pos = 0;
	for (size_t i = 1; i < strDNA.size(); i++)
	{
		string str1 = strDNA.substr(i) + strDNA.substr(0, i);
		string str2 = strDNA.substr(pos) + strDNA.substr(0, pos);
		if (str1 < str2){
			pos = i;
		}
	}
	cout << strDNA.substr(pos) + strDNA.substr(0, pos) << endl;
}

int main()
{
	int n = 0;
	cin >> n;
	string strDNA;
	for (int i = 0; i < n; i++)
	{
		cin >> strDNA;
		smallest(strDNA);
	}
	return 0;
}
/*
2
CGAGTCAGCT
CTCC
*/
