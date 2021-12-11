#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n = 0;
	cin >> n;
	string strAns;
	for (int i = 0; i < n; i++)
	{
		cin >> strAns;
		int consecutive = 0, score = 0;
		for (auto c : strAns)
		{
			if (c == 'O'){
				score++;
				score += consecutive;
				consecutive++;
			}
			else if(c == 'X'){
				consecutive = 0;
			}
		}
		cout << score << endl;
	}
	return 0;
}
/*
5
OOXXOXXOOO
OOXXOOXXOO
OXOXOXOXOXOXOX
OOOOOOOOOO
OOOOXOOOOXOOOOX
*/
