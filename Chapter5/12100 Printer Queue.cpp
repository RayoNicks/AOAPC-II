#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int main()
{
	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		int n = 0, m = 0, priority;
		cin >> n >> m;
		deque<pair<int, bool>> queue;
		vector<int> higher(10, 0);
		for (int i = 0; i < n; i++)
		{
			cin >> priority;
			queue.push_back(pair<int, bool>(priority, i == m));
			for (int j = 1; j < priority; j++)
			{
				higher[j]++;
			}
		}
		int minute = 0;
		while (1) {
			if (higher[queue.front().first] > 0) {
				queue.push_back(queue.front());
				queue.pop_front();
			}
			else {
				minute++;
				if (queue.front().second) break;
				else {
					for (int j = 1; j < queue.front().first; j++)
					{
						higher[j]--;
					}
					queue.pop_front();
				}
			}
		}
		cout << minute << endl;
	}
	return 0;
}
/*
3
1 0
5
4 2
1 2 3 4
6 0
1 1 9 1 1 1
*/
