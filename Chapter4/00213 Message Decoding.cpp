#include <iostream>
#include <string>
#include <cstring>

using namespace std;

void decode(const string &strHdr, const string &strBin)
{
	char chDecode[7][128];
	int len = 1, i = 0;
	memset(chDecode, 0, 7 * 128 * sizeof(char));
	for (size_t idx = 0; idx < strHdr.size();idx++)
	{
		chDecode[len - 1][i] = strHdr[idx];
		i++;
		if (i == ((1 << len) - 1)){
			len++;
			i = 0;
		}
	}
	size_t curr = 0;
	string strMsg;
	while (1){
		int len = stol(strBin.substr(curr, 3), nullptr, 2);
		curr += 3;
		if (len == 0) break;
		while (1){
			int i = stol(strBin.substr(curr, len), nullptr, 2);
			curr += len;
			if (chDecode[len - 1][i] == '\0') break;
			else strMsg.push_back(chDecode[len - 1][i]);
		}
	}
	cout << strMsg << endl;
	return;
}

int main()
{
	string strHdr;
	while (getline(cin, strHdr)){
		string strLine, strBin;
		char ch;
		while (ch = cin.peek()){
			if (ch != '0' && ch != '1') break;
			getline(cin, strLine);
			strBin += strLine;
		}
		decode(strHdr, strBin);
	}
	return 0;
}
/*
TNM AEIOU
0010101100011
1010001001110110011
11000
$#**\
0100000101101100011100101000
*/
