#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define BOUND 8

using namespace std;

pair<int, int> getPosition(const vector<vector<char>> &vvcBoard, char chCurr,
	int i, int j, int dirx, int diry)
{
	int bracket = 0;
	i += dirx, j += diry;
	while (i >= 0 && i < BOUND && j >= 0 && j < BOUND){
		if (vvcBoard[i][j] == '-'){
			if (bracket >= 1) return pair<int, int>(i, j);
			else return pair<int, int>(-1, -1);
		}
		else if (vvcBoard[i][j] == chCurr){
			return pair<int, int>(-1, -1);
		}
		i += dirx, j += diry;
		bracket++;
	}
	return pair<int, int>(-1, -1);
}

vector<pair<int, int>> processL(vector<vector<char>> &vvcBoard, char chCurr)
{
	vector<pair<int, int>> vecPos;
	pair<int, int> pos;
	for (int i = 0; i < BOUND; i++)
	{
		for (int j = 0; j < BOUND; j++)
		{
			if (vvcBoard[i][j] == chCurr){
				//up
				pos = getPosition(vvcBoard, chCurr, i, j, -1, 0);
				if (pos.first != -1) vecPos.push_back(pos);
				//up right
				pos = getPosition(vvcBoard, chCurr, i, j, -1, 1);
				if (pos.first != -1) vecPos.push_back(pos);
				//right
				pos = getPosition(vvcBoard, chCurr, i, j, 0, 1);
				if (pos.first != -1) vecPos.push_back(pos);
				//down right
				pos = getPosition(vvcBoard, chCurr, i, j, 1, 1);
				if (pos.first != -1) vecPos.push_back(pos);
				//down
				pos = getPosition(vvcBoard, chCurr, i, j, 1, 0);
				if (pos.first != -1) vecPos.push_back(pos);
				//down left
				pos = getPosition(vvcBoard, chCurr, i, j, 1, -1);
				if (pos.first != -1) vecPos.push_back(pos);
				//left
				pos = getPosition(vvcBoard, chCurr, i, j, 0, -1);
				if (pos.first != -1) vecPos.push_back(pos);
				//up left
				pos = getPosition(vvcBoard, chCurr, i, j, -1, -1);
				if (pos.first != -1) vecPos.push_back(pos);
			}
		}
	}
	return vecPos;
}

void chgColor(vector<vector<char>> &vvcBoard, char chCurr,
	int i, int j, int dirx, int diry)
{
	int currx = i, curry = j;
	i += dirx, j += diry;
	while (i >= 0 && i < BOUND && j >= 0 && j < BOUND){
		if (vvcBoard[i][j] == '-'){
			return;
		}
		else if (vvcBoard[i][j] == chCurr){
			i = currx + dirx, j = curry + diry;
			while (i >= 0 && i < BOUND && j >= 0 && j < BOUND){
				if (vvcBoard[i][j] == chCurr) break;
				vvcBoard[i][j] = chCurr;
				i += dirx, j += diry;
			}
			return;
		}
		i += dirx, j += diry;
	}
	return;
}

void processM(vector<vector<char>> &vvcBoard, char chCurr, int i, int j)
{
	vvcBoard[i][j] = chCurr;
	//up
	chgColor(vvcBoard, chCurr, i, j, -1, 0);
	//up right
	chgColor(vvcBoard, chCurr, i, j, -1, 1);
	//right
	chgColor(vvcBoard, chCurr, i, j, 0, 1);
	//down right
	chgColor(vvcBoard, chCurr, i, j, 1, 1);
	//down
	chgColor(vvcBoard, chCurr, i, j, 1, 0);
	//down left
	chgColor(vvcBoard, chCurr, i, j, 1, -1);
	//left
	chgColor(vvcBoard, chCurr, i, j, 0, -1);
	//up left
	chgColor(vvcBoard, chCurr, i, j, -1, -1);
}

void processCmd(const string &strCmd,
	vector<vector<char>> &vvcBoard, bool &bCurr)
{
	vector<pair<int, int>> vecPos = processL(vvcBoard, bCurr ? 'W' : 'B');
	if (strCmd[0] == 'L'){
		if (vecPos.empty()){
			cout << "No legal move." << endl;
			return;
		}
		sort(vecPos.begin(), vecPos.end(),
			[](const pair<int, int> &pos1, const pair<int, int> &pos2)->bool
		{
			if (pos1.first < pos2.first) return true;
			else if (pos1.first == pos2.first) return pos1.second < pos2.second;
			else return false;
		});
		auto iterEnd = unique(vecPos.begin(), vecPos.end(),
			[](const pair<int, int> &pos1, const pair<int, int> &pos2)->bool
		{
			return pos1 == pos2;
		});
		for (auto iter = vecPos.begin(); iter != iterEnd - 1; iter++)
		{
			cout << '(' << iter->first + 1 << ',' << iter->second + 1 << ") ";
		}
		cout << '(' << (iterEnd - 1)->first + 1 << ',' << (iterEnd - 1)->second + 1 << ")\n";
	}
	else if (strCmd[0] == 'M'){
		int x = strCmd[1] - '0' - 1, y = strCmd[2] - '0' - 1;
		if (vecPos.empty()) processM(vvcBoard, bCurr ? 'B' : 'W', x, y);
		else{
			processM(vvcBoard, bCurr ? 'W' : 'B', x, y);
			bCurr = !bCurr;
		}
		int black = 0, white = 0;
		for (int i = 0; i < BOUND; i++)
		{
			for (int j = 0; j < BOUND; j++)
			{
				if (vvcBoard[i][j] == 'W') white++;
				else if (vvcBoard[i][j] == 'B') black++;
			}
		}
		cout << "Black -";
		if (black >= 10) cout << ' ' << black;
		else cout << "  " << black;
		cout << " White -";
		if (white >= 10) cout << ' ' << white << endl;
		else cout << "  " << white << endl;
	}
}

int main()
{
	int games = 0;
	cin >> games;
	cin.get();
	for (int g = 0; g < games; g++)
	{
		if (g != 0) cout << endl;
		vector<vector<char>> vvcBoard(BOUND, vector<char>(BOUND, '-'));
		for (size_t i = 0; i < BOUND; i++)
		{
			for (size_t j = 0; j < BOUND; j++)
			{
				cin >> vvcBoard[i][j];
			}
			cin.get();
		}
		bool bCurr;
		char chCurr;
		cin >> chCurr;
		//false黑先，true表示白先
		if (chCurr == 'B') bCurr = false;
		else bCurr = true;
		string strCmd;
		cin.get();
		while (cin >> strCmd){
			if (strCmd == "Q"){
				for (size_t i = 0; i < BOUND; i++)
				{
					for (size_t j = 0; j < BOUND; j++)
					{
						cout << vvcBoard[i][j];
					}
					cout << endl;
				}
				break;
			}
			processCmd(strCmd, vvcBoard, bCurr);
		}
	}
	return 0;
}
/*
2
--------
--------
--------
---WB---
---BW---
--------
--------
--------
W
L
M35
L
Q
WWWWB---
WWWB----
WWB-----
WB------
--------
--------
--------
--------
B
L
M25
L
Q
*/
