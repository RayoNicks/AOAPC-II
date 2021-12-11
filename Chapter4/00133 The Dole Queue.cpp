#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void select(const int N, const int k, const int m)
{
	vector<int> viNum;
	ostringstream oss;
	int off = 0;
	for (int i = 1; i <= N; i++)
	{
		viNum.push_back(i);
	}
	int i = 0, j = N - 1;
	while (1){
		int cnt1 = 0, cnt2 = 0;
		while (1){
			if (viNum[i] != 0){
				cnt1++;
				if (cnt1 == k) break;
			}
			i++;
			if (i >= N) i -= N;
		}
		while (1){
			if (viNum[j] != 0){
				cnt2++;
				if (cnt2 == m) break;
			}
			j--;
			if (j < 0) j += N;
		}
		if (i == j){
			if (viNum[i] >= 10) oss << ' ' << viNum[i] << ',';
			else oss << "  " << viNum[i] << ',';
			off += 1;
		}
		else{
			if (viNum[i] >= 10) oss << ' ' << viNum[i];
			else oss << "  " << viNum[i];
			if (viNum[j] >= 10) oss << ' ' << viNum[j] << ',';
			else oss << "  " << viNum[j] << ',';
			off += 2;
		}
		viNum[i] = 0, viNum[j] = 0;
		if (off == N) break;
	}
	string strOutput(oss.str());
	strOutput.pop_back();
	cout << strOutput << endl;
}

int main()
{
	int N = 0, k = 0, m = 0;
	while (cin >> N >> k >> m){
		if (N == 0 && k == 0 && m == 0) break;
		select(N, k, m);
	}
	return 0;
}
/*
10 4 3
0 0 0
*/
