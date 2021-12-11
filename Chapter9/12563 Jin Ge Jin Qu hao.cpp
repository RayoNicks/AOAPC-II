#include <iostream>
#include <vector>

using namespace std;

void findMaximumSung(const vector<int> &viLength, const int time)
{
	size_t song = viLength.size();
	vector<vector<pair<int, int>>> sung(viLength.size(), vector<pair<int, int>>(time, make_pair<int, int>(0, 0)));
	for (int t = viLength[0]; t < time; t++)
	{
		sung[0][t].first = 1;
		sung[0][t].second = viLength[0];
	}
	for (size_t s = 1; s < song; s++)
	{
		for (int t = 0; t < time; t++)
		{
			sung[s][t] = sung[s - 1][t];
			if (t >= viLength[s]) {
				if (sung[s][t].first < sung[s - 1][t - viLength[s]].first + 1) {
					sung[s][t].first = sung[s - 1][t - viLength[s]].first + 1;
					sung[s][t].second = sung[s - 1][t - viLength[s]].second + viLength[s];
				}
				else if (sung[s][t].first == sung[s - 1][t - viLength[s]].first + 1) {
					if (sung[s][t].second < sung[s - 1][t - viLength[s]].second + viLength[s]) {
						sung[s][t].second = sung[s - 1][t - viLength[s]].second + viLength[s];
					}
				}
			}
		}
	}
	int maxTime = 0, maxSung = 0;
	for (size_t t = time; t > 0; t--)
	{
		if (sung[song - 1][t - 1].first > maxSung) {
			maxSung = sung[song - 1][t - 1].first;
			maxTime = sung[song - 1][t - 1].second;
		}
		else if (sung[song - 1][t - 1].first == maxSung) {
			if (sung[song - 1][t - 1].second > maxTime) {
				maxTime = sung[song - 1][t - 1].second;
			}
		}
	}
	cout << maxSung + 1 << ' ' << maxTime + 678 << endl;
}

int main()
{
	int Test, n, t;
	cin >> Test;
	for (int test = 0; test < Test; test++)
	{
		cin >> n >> t;
		vector<int> viLength(n, 0);
		for (int song = 0; song < n; song++)
		{
			cin >> viLength[song];
		}
		cout << "Case " << test + 1 << ": ";
		findMaximumSung(viLength, t);
	}
	return 0;
}
/*
2
3 100
60 70 80
3 100
30 69 70
*/
