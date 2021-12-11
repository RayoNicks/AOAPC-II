#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool check(const string &strCipher, const string &strPlain)
{
	vector<int> viCntCipher(26, 0), viCntPlain(26, 0);
	for (size_t i = 0; i < strCipher.size(); i++)
	{
		viCntCipher[strCipher[i] - 'A']++;
	}
	for (size_t i = 0; i < strPlain.size(); i++)
	{
		viCntPlain[strPlain[i] - 'A']++;
	}
	sort(viCntCipher.begin(), viCntCipher.end());
	sort(viCntPlain.begin(), viCntPlain.end());
	for (size_t i = 0; i < viCntCipher.size(); i++)
	{
		if (viCntCipher[i] != viCntPlain[i]) return false;
	}
	return true;
}

int main()
{
	string strCipher, strPlain;
	while (cin >> strCipher >> strPlain){
		if (check(strCipher, strPlain)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
/*
JWPUDJSTVP
VICTORIOUS
MAMA
ROME
HAHA
HEHE
AAA
AAA
NEERCISTHEBEST
SECRETMESSAGES
*/
