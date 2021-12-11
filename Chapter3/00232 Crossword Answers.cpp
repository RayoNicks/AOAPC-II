#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int cnt = 0;
	while (1){
		cnt++;
		vector<vector<char>> vvcSquare(10, vector<char>(10, '*'));
		vector<vector<int>> vviNumber(10, vector<int>(10, 0));
		int row = 0, col = 0;
		int iNumber = 1;
		cin >> row;
		if (row == 0) break;
		else if (cnt != 1) cout << endl;
		cin >> col;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cin >> vvcSquare[i][j];
			}
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (vvcSquare[i][j] == '*') continue;
				if (i - 1 < 0 || j - 1 < 0){
					vviNumber[i][j] = iNumber++;
				}
				else if (vvcSquare[i - 1][j] == '*' || vvcSquare[i][j - 1] == '*'){
					vviNumber[i][j] = iNumber++;
				}
			}
		}
		cout << "puzzle #" << cnt << ':' << endl;
		cout << "Across" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (vviNumber[i][j] != 0){
					if (vviNumber[i][j] >= 10) cout << ' ';
					else cout << "  ";
					cout << vviNumber[i][j] << '.';
					int k = j;
					for (; k < col; k++)
					{
						if (vvcSquare[i][k] != '*') cout << vvcSquare[i][k];
						else break;
					}
					cout << endl;
					j = k;
				}
			}
		}
		cout << "Down" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (vviNumber[i][j] != 0){
					if (vviNumber[i][j] >= 10) cout << ' ';
					else cout << "  ";
					cout << vviNumber[i][j] << '.';
					for (int k = i; k < row; k++)
					{
						if (vvcSquare[k][j] != '*'){
							vviNumber[k][j] = 0;
							cout << vvcSquare[k][j];
						}
						else break;
					}
					cout << endl;
				}
			}
		}
	}
	return 0;
}
/*
2 2
AT
*O
6 7
AIM*DEN
*ME*ONE
UPON*TO
SO*ERIN
*SA*OR*
IES*DEA
0
*/
