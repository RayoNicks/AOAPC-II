#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	size_t n, m;
	while (1) {
		cin >> n >> m;
		if (n == 0 && m == 0) break;
		vector<list<size_t>> relations(n);
		vector<size_t> order;
		vector<bool> done(n, false);
		for (size_t k = 0; k < m; k++)
		{
			size_t i, j;
			cin >> i >> j;
			relations[j - 1].push_back(i - 1);
		}
		while (1) {
			for (size_t i = 0; i < relations.size(); i++)
			{
				if (!done[i] && relations[i].empty()) {
					order.push_back(i);
					done[i] = true;
					for (size_t j = 0; j < relations.size(); j++)
					{
						relations[j].remove(i);
					}
					break;
				}
			}
			if (order.size() == n) break;
		}
		for (size_t no : order)
		{
			cout << no + 1 << ' ';
		}
		cout << endl;
	}
	return 0;
}
/*
5 4
1 2
2 3
1 3
1 5
0 0
*/
