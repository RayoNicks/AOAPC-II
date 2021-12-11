#include <iostream>
#include <deque>

using namespace std;

int main()
{
	int n = 0;
	while (cin >> n) {
		if (n == 0) break;
		else if (n == 1) {
			cout << "Discarded cards:\n" << "Remaining card: 1" << endl;
			continue;
		}
		else {
			deque<int> cards;
			for (int i = 1; i <= n; i++)
			{
				cards.push_back(i);
			}
			cout << "Discarded cards: ";
			while (cards.size() > 2) {
				cout << cards.front() << ", ";
				cards.pop_front();
				cards.push_back(cards.front());
				cards.pop_front();
			}
			cout << cards.front() << endl;
			cout << "Remaining card: " << cards.back() << endl;
		}
	}
	return 0;
}
/*
7
19
10
6
0
1 2 3 4 5 6
3 4 5 6 2
5 6 2 4
2 4 6
6 4
*/
