#include <iostream>
#include <vector>

using namespace std;

bool reorganize(const vector<int> &B)
{
	vector<int> station;
	int a = 1;
	auto iter = B.begin();
	while (iter != B.end()) {
		if (station.empty() || *iter > station.back()) station.push_back(a++);
		else if(*iter == station.back()){
			station.pop_back();
			iter++;
		}
		else {
			return false;
		}
	}
	return true;
}

int main()
{
	int N = 0;
	while (cin >> N) {
		if (N == 0) break;
		vector<int>	B(N);
		while (1) {
			cin >> B[0];
			if (B[0] == 0) {
				cout << endl;
				break;
			}
			for (int i = 1; i < N; i++)
			{
				cin >> B[i];
			}
			if (reorganize(B)) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
	return 0;
}
/*
5
1 2 3 4 5
5 4 1 2 3
0
6
6 5 4 3 2 1
0
0
*/
