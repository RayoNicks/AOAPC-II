#include <iostream>
#include <vector>

using namespace std;

bool drawSquare(size_t i, size_t j, size_t len,
	const vector<vector<bool>> &vvbHorLine,
	const vector<vector<bool>> &vvbVerLine)
{
	for (size_t step = 1; step <= len; step++)
	{
		if (!vvbHorLine[i][j++]) return false;
	}
	for (size_t step = 1; step <= len; step++)
	{
		if (!vvbVerLine[i++][j]) return false;
	}
	for (size_t step = 1; step <= len; step++)
	{
		if (!vvbHorLine[i][--j]) return false;
	}
	for (size_t step = 1; step <= len; step++)
	{
		if (!vvbVerLine[--i][j]) return false;
	}
	return true;
}

void cntSquare(const vector<vector<bool>> &vvbHorLine, 
	const vector<vector<bool>> &vvbVerLine, size_t n)
{
	vector<int> viSquare(n, 0);
	//枚举每个点
	for (size_t i = 0; i < n - 1; i++)
	{
		for (size_t j = 0; j < n - 1; j++)
		{
			//枚举所有可能的边长
			for (size_t len = 1; len < n - i && len < n - j; len++)
			{
				if (drawSquare(i, j, len, vvbHorLine, vvbVerLine)){
					viSquare[len]++;
				}
			}
		}
	}
	bool bEmpty = true;
	for (size_t idx = 1; idx < n; idx++)
	{
		if (viSquare[idx] != 0){
			bEmpty = false;
			cout << viSquare[idx] << " square (s) of size " << idx << endl;
		}
	}
	if (bEmpty){
		cout << "No completed squares can be found." << endl;
	}
}

int main()
{
	int cnt = 1;
	size_t n, m;
	while (cin >> n >> m){
		if (cnt != 1){
			cout << "\n**********************************\n" << endl;
		}
		cin.get();
		char ch;
		int i, j;
		vector<vector<bool>> vvbHorLine(n, vector<bool>(n, false));
		vector<vector<bool>> vvbVerLine(n, vector<bool>(n, false));
		for (size_t idx = 0; idx < m; idx++)
		{
			cin >> ch;
			cin >> i >> j;
			cin.get();
			if (ch == 'H') vvbHorLine[i - 1][j - 1] = true;
			else if (ch == 'V') vvbVerLine[j - 1][i - 1] = true;
		}
		cout << "Problem #" << cnt++ << endl << endl;
		cntSquare(vvbHorLine, vvbVerLine, n);
	}
	return 0;
}
/*
4
16
H 1 1
H 1 3
H 2 1
H 2 2
H 2 3
H 3 2
H 4 2
H 4 3
V 1 1
V 2 1
V 2 2
V 2 3
V 3 2
V 4 1
V 4 2
V 4 3
2
3
H 1 1
H 2 1
V 2 1
*/
