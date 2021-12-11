#include <iostream>
#include <cmath>
#include <set>
#include <vector>

using namespace std;

bool IsDucciSeq(const vector<int> &seq)
{
	set<vector<int>> state;
	vector<int> tmp(seq);
	state.insert(seq);
	while (1) {
		int first = tmp.front();
		bool zero = true;
		for (size_t i = 0; i < tmp.size() - 1; i++)
		{
			tmp[i] = abs(tmp[i + 1] - tmp[i]);
			if (tmp[i] != 0) {
				zero = false;
			}
		}
		tmp.back() = abs(first - tmp.back());
		if (tmp.back() != 0) {
			zero = false;
		}
		if (zero) {
			return true;
		}
		else if (state.find(tmp) == state.end()) {
			state.insert(tmp);
		}
		else {
			return false;
		}
	}
}

int main()
{
	int T;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int n;
		cin >> n;
		vector<int> seq(n, 0);
		for (int i = 0; i < n; i++)
		{
			cin >> seq[i];
		}
		if (IsDucciSeq(seq)) {
			cout << "ZERO" << endl;
		}
		else {
			cout << "LOOP" << endl;
		}
	}
	return 0;
}
/*
4
4
8 11 2 7
5
4 2 0 2 0
7
0 0 0 0 0 0 0
6
1 2 3 1 2 3
*/
