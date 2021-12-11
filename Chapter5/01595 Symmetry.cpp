#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
#include <vector>

using namespace std;

int GetSymmetricLine(vector<int> &horizontal)
{
	sort(horizontal.begin(), horizontal.end());
	if (horizontal.size() % 2 == 1) {
		return 2 * horizontal[horizontal.size() / 2];
	}
	else {
		int x = horizontal.front() + horizontal.back();
		for (size_t i = 1; i < horizontal.size() / 2; i++)
		{
			if (horizontal[i] + horizontal[horizontal.size() - 1 - i] != x) {
				return INT_MAX;
			}
		}
		return x;
	}
}

int main()
{
	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int N = 0;
		cin >> N;
		map<int, vector<int>> points;
		for (int n = 0; n < N; n++)
		{
			int x, y;
			cin >> x >> y;
			points[y].push_back(x);
		}
		int vertical = GetSymmetricLine(points.begin()->second);
		if (vertical == INT_MAX) {
			cout << "NO" << endl;
		}
		else {
			bool IsSymm = true;
			for (auto iter = ++points.begin(); iter != points.end(); iter++)
			{
				if (GetSymmetricLine(iter->second) != vertical) {
					IsSymm = false;
					break;
				}
			}
			if (IsSymm) {
				cout << "YES" << endl;
			}
			else{
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}
/*
3
5
-2 5
0 0
6 5
4 0
2 3
4
2 3
0 4
4 0
0 0
4
5 14
6 10
5 10
6 14
*/
