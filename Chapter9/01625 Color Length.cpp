#include <iostream>
#include <string>
#include <vector>
#include <climits>

#define A_2_O(c) ((c) - 'A')

using namespace std;

void calPosition(const string &str1, const string &str2, vector<pair<size_t, size_t>> &FstPos, vector<pair<size_t, size_t>> &LstPos)
{
	size_t i = 0, j = 0;
	while (i < str1.size() && j < str2.size()) {
		LstPos[A_2_O(str1[i++])].first = i;
		LstPos[A_2_O(str2[j++])].second = j;
	}
	while (i < str1.size()) {
		LstPos[A_2_O(str1[i++])].first = i;
	}
	while (j < str2.size()) {
		LstPos[A_2_O(str2[j++])].second = j;
	}

	while (i > 0 && j > 0) {
		FstPos[A_2_O(str1[--i])].first = i + 1;
		FstPos[A_2_O(str2[--j])].second = j + 1;
	}
	while (i > 0) {
		FstPos[A_2_O(str1[--i])].first = i + 1;
	}
	while (j > 0) {
		FstPos[A_2_O(str2[--j])].second = j + 1;
	}
}

void findMinimumColorLength(const string &str1, const string &str2)
{
	vector<vector<int>> Length(str1.size() + 2, vector<int>(str2.size() + 2, INT_MAX));
	vector<vector<int>> Left(str1.size() + 1, vector<int>(str2.size() + 1, 0));
	vector<pair<size_t, size_t>> FstPos(26, pair<size_t, size_t>(UINT_MAX, UINT_MAX));
	vector<pair<size_t, size_t>> LstPos(26, pair<size_t, size_t>(UINT_MAX, UINT_MAX));

	calPosition(str1, str2, FstPos, LstPos);

	Left[0][0] = 0;
	for (size_t i = 0; i <= str1.size(); i++)
	{
		for (size_t j = 0; j <= str2.size(); j++)
		{
			for (char c = A_2_O('A'); c <= A_2_O('Z'); c++)
			{
				if ((
					(FstPos[c].first != UINT_MAX && FstPos[c].first <= i)
					|| (FstPos[c].second != UINT_MAX && FstPos[c].second <= j)
					) && (
					(LstPos[c].first != UINT_MAX && LstPos[c].first > i)
						|| (LstPos[c].second != UINT_MAX && LstPos[c].second > j)
						)) {
					Left[i][j]++;
				}
			}
		}
	}

	Length[0][0] = 0;
	for (size_t i = 0; i <= str1.size(); i++)
	{
		for (size_t j = 0; j <= str2.size(); j++)
		{
			if (Length[i + 1][j] > Length[i][j] + Left[i][j]) {
				Length[i + 1][j] = Length[i][j] + Left[i][j];
			}
			if (Length[i][j + 1] > Length[i][j] + Left[i][j]) {
				Length[i][j + 1] = Length[i][j] + Left[i][j];
			}
		}
	}

	cout << Length[str1.size()][str2.size()] << endl;
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		string str1, str2;
		cin >> str1 >> str2;
		findMinimumColorLength(str1, str2);
	}
	return 0;
}
/*
2
AAABBCY
ABBBCDEEY
GBBY
YRRGB
*/
