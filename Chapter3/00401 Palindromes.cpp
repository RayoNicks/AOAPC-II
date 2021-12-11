#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
	const string strMirror("A   3  HIL JM O   2TUVWXY51SE Z  8 ");
	map<char, char> mcc;
	for (char c = 'A'; c <= 'Z'; c++)
		mcc[c] = strMirror[c - 'A'];
	for (char c = '1'; c <= '9'; c++)
		mcc[c] = strMirror[c - '1' + 26];
	string strLine;
	while (cin >> strLine){
		bool bp = true, bm = true;
		for (size_t i = 0; i + i < strLine.size(); i++)
		{
			if (strLine[i] != strLine[strLine.size() - 1 - i]) bp = false;
			if (strLine[i] != mcc[strLine[strLine.size() - 1 - i]]) bm = false;
		}
		if (bp && bm){
			cout << strLine << " -- is a mirrored palindrome." << endl << endl;
		}
		else if (bp){
			cout << strLine << " -- is a regular palindrome." << endl << endl;
		}
		else if (bm){
			cout << strLine << " -- is a mirrored string." << endl << endl;
		}
		else{
			cout << strLine << " -- is not a palindrome." << endl << endl;
		}
	}
	return 0;
}
/*
NOTAPALINDROME
ISAPALINILAPASI
2A3MEAS
ATOYOTA
*/
