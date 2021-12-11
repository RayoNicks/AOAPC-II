#include <iostream>
#include <map>

using namespace std;

int main()
{
	int n = 0;
	while (cin >> n) {
		if (n == 0) break;
		map<pair<int, int>, size_t> locations;
		for (int i = 0; i < n; i++)
		{
			pair<int, int> location, exchange;
			cin >> location.first >> location.second;
			exchange.second = location.first;
			exchange.first = location.second;
			if (locations.find(exchange) == locations.end()) {
				locations[location]++;
			}
			else if (--locations[exchange] == 0) {
					locations.erase(exchange);
			}
			else;
		}
		if (locations.empty()) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
/*
10
1 2
2 1
3 4
4 3
100 200
200 100
57 2
2 57
1 2
2 1
10
1 2
3 4
5 6
7 8
9 10
11 12
13 14
15 16
17 18
19 20
0
*/
