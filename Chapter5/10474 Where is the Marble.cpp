#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void find(const vector<int> &vi, const int q)
{
	for (size_t i = 0; i < vi.size(); i++)
	{
		if (vi[i] == q){
			cout << q << " found at " << i + 1 << endl;
			return;
		}
	}
	cout << q << " not found" << endl;
}

int main()
{
	int N, Q, Case = 1;
	while (cin >> N >> Q){
		if (N == 0 && Q == 0) break;
		vector<int> vi(N, 0);
		for (int i = 0; i < N; i++)
		{
			cin >> vi[i];
		}
		sort(vi.begin(), vi.end());
		cout << "CASE# " << Case++ << ':' << endl;
		int q;
		for (int i = 0; i < Q; i++)
		{
			cin >> q;
			find(vi, q);
		}
	}
	return 0;
}
/*
4 1
2
3
5
1
5
5 2
1
3
3
3
1
2
3
0 0
*/
