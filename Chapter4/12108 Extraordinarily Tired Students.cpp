#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main()
{
	int n = 0, a, b, c;
	int t = 1;
	while (cin >> n){
		if (n == 0) break;
		vector<int> viAwaken, viSleep;
		set<string> sstrState;
		string strState;
		vector<bool> vbAwaken;
		for (int i = 0; i < n; i++)
		{
			cin >> a >> b >> c;
			viAwaken.push_back(a);
			viSleep.push_back(b);
			strState.push_back(c + '0');//10”√:±Ì æ
			if (c <= a) vbAwaken.push_back(true);
			else vbAwaken.push_back(false);
		}
		sstrState.insert(strState);
		int minute = 1;
		while (1){
			int cnt = 0, period;
			for (auto b : vbAwaken)
			{
				if (b) cnt++;
			}
			if (cnt == n) break;
			for (int i = 0; i < n; i++)
			{
				period = strState[i] - '0' + 1;
				if (period <= viAwaken[i]);
				else if (period == viAwaken[i] + 1){
					if (cnt < n - cnt) vbAwaken[i] = false;
					else period = 1;
				}
				else if (period == viAwaken[i] + viSleep[i] + 1){
					vbAwaken[i] = true;
					period = 1;
				}
				strState[i] = period + '0';
			}
			if (sstrState.find(strState) != sstrState.end()){
				minute = -1;
				break;
			}
			else sstrState.insert(strState);
			minute++;
		}
		cout << "Case " << t++ << ": " << minute << endl;
	}
	return 0;
}
/*
3
2 4 1
1 5 2
1 4 3
3
1 2 1
1 2 2
1 2 3
0
*/
