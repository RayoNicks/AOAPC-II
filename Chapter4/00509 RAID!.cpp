#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

void printRAID(const vector<vector<string>> &raid)
{
	for (size_t i = 0; i < raid.size(); i++)
	{
		for (size_t j = 0; j < raid[0].size(); j++)
		{
			//if (j != i % raid[0].size())
				cout << raid[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

string recoverRAID(vector<vector<string>> &raid, bool bOdd)
{
	for (size_t pos = 0; pos < raid[0][0].size(); pos++)
	{
		for (size_t i = 0; i < raid.size(); i++)
		{
			//记录坏块数量，和坏块位置
			size_t disk = 0, bad = 0;
			char ucXor = '\0';
			for (size_t j = 0; j < raid[0].size(); j++)
			{
				if (raid[i][j][pos] == 'x'){
					if (bad == 0) disk = j;
					bad++;
				}
				else ucXor ^= (raid[i][j][pos] - '0');
			}
			if (bad > 1){
				return "";
			}
			else if (bad == 1){
				raid[i][disk][pos] = static_cast<char>(bOdd) ^ ucXor + '0';
			}
			else{
				if (ucXor != static_cast<char>(bOdd)){
					return "";
				}
			}
		}
	}
	string strBinData, strHexData;
	for (size_t i = 0; i < raid.size(); i++)
	{
		for (size_t j = 0; j < raid[0].size(); j++)
		{
			if (j != i % raid[0].size()) strBinData.append(raid[i][j]);
		}
	}
	while ((strBinData.size() & 0x03) != 0) strBinData.push_back('0');
	ostringstream oss;
	for (size_t pos = 0; pos < strBinData.size(); pos+=4)
	{
		oss << hex << setw(1) << stoul(strBinData.substr(pos, 4), nullptr, 2);
	}
	strHexData = oss.str();
	for (char &ch : strHexData)
	{
		if (isalpha(ch)) ch = toupper(ch);
	}
	return strHexData;
}

int main()
{
	int d = 0, s = 0, b = 0, set = 1;
	char ch;;
	bool bOdd;
	while (cin >> d){
		if (d == 0) break;
		cin >> s >> b;
		cin.get();
		cin >> ch;
		if (ch == 'E') bOdd = false;
		else if (ch == 'O') bOdd = true;
		//行表示块，列表示磁盘
		cin.get();
		vector<vector<string>> raid(b, vector<string>(d, string(s, 'x')));
		string strData;
		for (int disk = 0; disk < d; disk++)
		{
			cin >> strData;
			auto iter = strData.begin();
			for (int block = 0; block < b; block++)
			{
				raid[block][disk].assign(iter, iter + s);
				iter += s;
			}
		}
		//printRAID(raid);
		strData = recoverRAID(raid, bOdd);
		cout << "Disk set " << set++ << " is ";
		if (strData.empty()) cout << "invalid." << endl;
		else{
			cout << "valid, contents are: " << strData << endl;
		}
	}
	return 0;
}
/*
5 2 5
E
0001011111
0110111011
1011011111
1110101100
0010010111
3 2 5
E
0001111111
0111111011
xx11011111
3 5 1
O
11111
11xxx
x1111
0
*/
