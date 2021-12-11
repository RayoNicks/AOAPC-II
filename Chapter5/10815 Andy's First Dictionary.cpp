#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main()
{
	string strLine, strWord, strMangle;
	set<string> sstrDic;
	while (getline(cin, strLine)){
		if (strLine.empty()) continue;
		size_t begin = 0, end;
		while (begin < strLine.size()){
			while (begin < strLine.size() && !isalpha(strLine[begin])) begin++;
			end = begin;
			while (end < strLine.size() && isalpha(strLine[end])) end++;
			strWord = strLine.substr(begin, end - begin);
			if (strWord.empty()) break;
			for (auto &ch : strWord)
			{
				ch = tolower(ch);
			}
			sstrDic.insert(strWord);
			begin = end + 1;
		}
	}
	for (auto iter = sstrDic.begin(); iter != sstrDic.end(); iter++)
	{
		cout << *iter << endl;
	}
	return 0;
}
/*
Adventures in Disneyland

Two blondes were going to Disneyland when they came to a fork in the
road. The sign read: "Disneyland Left."

So they went home.
*/
