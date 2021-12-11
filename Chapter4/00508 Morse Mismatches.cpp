#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

void print(const vector<string> &vsMorse)
{
	for (auto iter = vsMorse.begin(); iter != vsMorse.end(); iter++)
	{
		cout << *iter << endl;
	}
}

void print(const map<string, string> &mssDic)
{
	for (auto iter = mssDic.begin(); iter != mssDic.end(); iter++)
	{
		cout << iter->first << ' ' << iter->second << endl;
	}
}

string getPerfectMatch(const map<string, string> &mssDic, const string &strWord)
{
	string strRet;
	int match = 0;
	for (auto iter = mssDic.begin(); iter != mssDic.end(); iter++)
	{
		if (iter->second == strWord){
			if (match == 0/* || iter->first.size() < strRet.size()*/) strRet.assign(iter->first);
			match++;
		}
	}
	if (match > 1){
		strRet.push_back('!');	
	}
	return strRet;
}

string getFuzzyMatch(const map<string, string> &mssDic, const string &strWord)
{
	string strRet;
	size_t cnt = 80;//编码最长80
	size_t del = 0, add = 0;
	for (auto iter = mssDic.begin(); iter != mssDic.end(); iter++)
	{
		size_t idx = 0;
		for (; idx < iter->second.size() && idx < strWord.size(); idx++)
		{
			if (iter->second[idx] != strWord[idx]) break;
		}
		//需要删除才可以匹配
		if (idx == iter->second.size() &&
			iter->second.size() < strWord.size()){
			del = strWord.size() - iter->second.size();
			if (del < cnt){
				strRet.assign(iter->first);
				strRet.push_back('?');
				cnt = del;
			}
		}
		//需要增加才可以匹配
		else if (idx == strWord.size() &&
			iter->second.size() > strWord.size()){
			add = iter->second.size() - strWord.size();
			if (add < cnt){
				strRet.assign(iter->first);
				strRet.push_back('?');
				cnt = add;
			}
		}
	}
	return strRet;
}

int main()
{
	string strLine, strPlain, strMorse;
	vector<string> vsMorse(26 + 10, "");
	while (getline(cin, strLine)){
		if (strLine.empty()) continue;
		else if (strLine == "*") break;
		istringstream iss(strLine);
		iss >> strPlain >> strMorse;
		if (isalpha(strPlain[0])){
			vsMorse[strPlain[0] - 'A'] = strMorse;
		}
		else if (isdigit(strPlain[0])){
			vsMorse[strPlain[0] - '0' + 26] = strMorse;
		}
	}
	//print(vsMorse);
	map<string, string> mssDic;
	while (getline(cin, strLine)){
		if (strLine.empty()) continue;
		else if (strLine == "*") break;
		for (auto ch : strLine)
		{
			if (isalpha(ch)) mssDic[strLine] += vsMorse[ch - 'A'];
			else if (isdigit(ch)) mssDic[strLine] += vsMorse[ch - '0' + 26];
		}
	}
	//print(mssDic);
	string strMatch, strWord;
	while (getline(cin, strLine)){
		if (strLine.empty()) continue;
		else if (strLine == "*") break;
		istringstream iss(strLine);
		while (iss >> strWord){
			strMatch = getPerfectMatch(mssDic, strWord);
			if (!strMatch.empty()) cout << strMatch << endl;
			else{
				strMatch = getFuzzyMatch(mssDic, strWord);
				cout << strMatch << endl;
			}
		}
	}
	return 0;
}
/*
A .-
B -...
C -.-.
D -..
E .
F ..-.
G --.
H ....
I ..
J .---
K -.-
L .-..
M --
N -.
O ---
P .--.
Q --.-
R .-.
S ...
T -
U ..-
V ...-
W .--
X -..-
Y -.--
Z --..
0 ------
1 .-----
2 ..---
3 ...--
4 ....-
5 .....
6 -....
7 --...
8 ---..
9 ----.
*
AN
EARTHQUAKE
EAT
GOD
HATH
IM
READY
TO
WHAT
WROTH
*
.--.....-- .....--....
--.----.. .--.-.----..
.--.....-- .--.
..-.-.-....--.-..-.--.-.
..-- .-...--..-.--
---- ..--
*
*/
