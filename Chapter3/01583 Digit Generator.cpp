#include <iostream>
#include <vector>

#define MAXN 100000

using namespace std;

int getGenerator(int n)
{
	int sum = n;
	while (n != 0){
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int main()
{
	vector<int> vi(MAXN + 1, 0);
	int generation = 0;
	for (int i = 1; i < MAXN; i++)
	{
		generation = getGenerator(i);
		if (generation <= MAXN && vi[generation] == 0){
			vi[generation] = i;
		}
	}
	int T = 0, num;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> num;
		cout << vi[num] << endl;
	}
	return 0;
}
/*
3
216
121
2005
*/
