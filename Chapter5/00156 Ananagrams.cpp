#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	string strWord, strLower;
	vector<string> vecstrDic;
	map<string, size_t> mWordCnt;
	set<string> sstr;
	while (cin >> strWord){
		if (strWord == "#") break;
		vecstrDic.push_back(strWord);
		strLower.assign(strWord);
		for (char &ch : strLower)
		{
			ch = tolower(ch);
		}
		sort(strLower.begin(), strLower.end());
		if (mWordCnt.find(strLower) == mWordCnt.end()) mWordCnt.insert(pair<string, size_t>(strLower, 1));
		else mWordCnt[strLower]++;
	}
	for (size_t i = 0; i < vecstrDic.size(); i++)
	{
		strLower.clear();
		for (auto ch : vecstrDic[i])
		{
			strLower.push_back(tolower(ch));
		}
		sort(strLower.begin(), strLower.end());
		if (mWordCnt.find(strLower)->second == 1) sstr.insert(vecstrDic[i]);
	}
	for (auto iter = sstr.begin(); iter != sstr.end(); iter++)
	{
		cout << *iter << endl;
	}
	return 0;
}
/*
ladder came tape soon leader acme RIDE lone Dreis peat
ScAlE orb eye Rides dealer NotE derail LaCeS drIed
noel dire Disk mace Rob dries
#
*/
