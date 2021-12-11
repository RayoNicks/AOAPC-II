#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
	int region = 1, m, n;
	while (cin >> m >> n){
		if (m == 0 && n == 0) break;
		vector<int> viElevation(m * n, 0);
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> viElevation[i * n + j];
			}
		}
		sort(viElevation.begin(), viElevation.end());
		size_t volume, elevation, cubic, cnt = 1;
		double dHigh, dPercent;
		cin >> volume;
		for (; cnt < viElevation.size(); cnt++)
		{
			elevation = viElevation[cnt] - viElevation[cnt - 1];
			cubic = elevation * cnt * 100;
			if (volume >= cubic) volume -= cubic;
			else break;
		}
		dHigh = ((double)volume) / cnt / 100 + viElevation[cnt - 1];
		cout << "Region " << region++ << endl;
		cout << "Water level is " << setprecision(2) << fixed << dHigh << " meters." << endl;
		cnt = 0;
		for (auto i : viElevation)
		{
			if (i < dHigh) cnt++;
		}
		dPercent = ((double)cnt) / viElevation.size() * 100.0;
		cout << dPercent << " percent of the region is under water." << endl;
		cout << endl;
	}
	return 0;
}
/*
3 3
25 37 45
51 12 34
94 83 27
10000
0 0
*/
