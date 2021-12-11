#include <iostream>

using namespace std;

int GetStopPosition(int D, int I)
{
	int root = 1;
	for (int d = 0; d < D - 1; d++)
	{
		if (I % 2 == 0) {
			root = 2 * root + 1;
			I /= 2;
		}
		else {
			root = 2 * root;
			I = (I + 1) / 2;
		}
	}
	return root;
}

int main()
{
	int cases;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		int D, I;
		cin >> D >> I;
		cout << GetStopPosition(D, I) << endl;
	}
	cin >> cases;
	return 0;
}
/*
5
4 2
3 4
10 1
2 2
8 128
-1
*/
