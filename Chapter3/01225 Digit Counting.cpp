#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	int n = 0, end;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> end;
		ostringstream oss;
		vector<int> vi(10, 0);
		for (int num = 1; num <= end; num++)
		{
			oss << num;
		}
		for (auto c : oss.str())
		{
			vi[c - '0']++;
		}
		for (auto iter = vi.begin(); iter != vi.end() - 1; iter++)
		{
			cout << *iter << ' ';
		}
		cout << vi.back() << endl;
	}
	return 0;
}
/*
2
3
13
*/
