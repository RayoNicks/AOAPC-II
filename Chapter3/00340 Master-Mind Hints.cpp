#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n = 0, cnt = 1;
	while (cin >> n){
		if (n == 0) break;
		cout << "Game " << cnt++ << ':' << endl;
		vector<int> viSecret(n, 0);
		vector<int> viSecretCnt(10, 0);
		vector<int> viGuess(n, 0);
		for (int i = 0; i < n; i++)
		{
			cin >> viSecret[i];
			viSecretCnt[viSecret[i]]++;
		}
		while (1){
			vector<int> viGuessCnt(10, 0);
			int strong = 0, match = 0;
			for (int i = 0; i < n; i++)
			{
				cin >> viGuess[i];
				viGuessCnt[viGuess[i]]++;
			}
			if (viGuess[0] == 0) break;
			for (int i = 0; i < n; i++)
			{
				if (viGuess[i] == viSecret[i]){
					strong++;
				}
			}
			for (int i = 1; i < 10; i++)
			{
				match += viGuessCnt[i] < viSecretCnt[i] ? viGuessCnt[i] : viSecretCnt[i];
			}
			cout << "    (" << strong << ',' << match - strong << ')' << endl;
		}
	}
	return 0;
}
/*
4
1 3 5 5
1 1 2 3
4 3 3 5
6 5 5 1
6 1 3 5
1 3 5 5
0 0 0 0
10
1 2 2 2 4 5 6 6 6 9
1 2 3 4 5 6 7 8 9 1
1 1 2 2 3 3 4 4 5 5
1 2 1 3 1 5 1 6 1 9
1 2 2 5 5 5 6 6 6 7
0 0 0 0 0 0 0 0 0 0
0
*/
