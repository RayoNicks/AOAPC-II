#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int cnt = 0;
	while (1){
		cnt++;
		vector<vector<char>> vvc(5, vector<char>(5, ' '));
		string strMove, strLine;
		int x = 0, y = 0;
		for (size_t i = 0; i < 5; i++)
		{
			getline(cin, strLine);
			for (size_t j = 0; j < strLine.size() && j < 5; j++)
			{
				vvc[i][j] = strLine[j];	
			}
		}
		for (size_t i = 0; i < 5; i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				if (vvc[i][j] == ' ') x = i, y = j;
			}
		}
		while (getline(cin, strLine)){
			strMove += strLine;
			if (strLine.back() == '0') break;
		}
		strMove.pop_back();
		bool bIllegal = false;
		for (char ch : strMove)
		{
			if (ch == 'A'){
				if (x - 1 < 0){
					bIllegal = true;
					break;
				}
				else{
					vvc[x][y] = vvc[x - 1][y];
					vvc[x - 1][y] = ' ';
					x--;
				}
			}
			else if (ch == 'B'){
				if (x + 1 >= 5){
					bIllegal = true;
					break;
				}
				else{
					vvc[x][y] = vvc[x + 1][y];
					vvc[x + 1][y] = ' ';
					x++;
				}
			}
			else if (ch == 'L'){
				if (y - 1 < 0){
					bIllegal = true;
					break;
				}
				else{
					vvc[x][y] = vvc[x][y - 1];
					vvc[x][y - 1] = ' ';
					y--;
				}
			}
			else if (ch == 'R'){
				if (y +1 >= 5){
					bIllegal = true;
					break;
				}
				else{
					vvc[x][y] = vvc[x][y + 1];
					vvc[x][y + 1] = ' ';
					y++;
				}
			}
			else{
				bIllegal = true;
			}
		}
		cout << "Puzzle #" << cnt << ':' << endl;
		if (bIllegal) cout << "This puzzle has no final configuration." << endl;
		else{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					cout << vvc[i][j] << ' ';
				}
				cout << vvc[i][4] << endl;
			}
		}
		if (cin.peek() == 'Z') break;
		else cout << endl;
	}
	return 0;
}
/*
TRGSJ
XDOKI
M VLN
WPABE
UQHCF
ARRBBL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAA
LLLL0
ABCDE
FGHIJ
KLMNO
PQRS
TUVWX
AAAAABBRRRLL0
Z
*/
