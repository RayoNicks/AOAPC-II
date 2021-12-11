#include <iostream>
#include <vector>

using namespace std;

struct Cube
{
	int length, width, height;
	Cube(const int &l, const int &w, const int &h)
		:length(l), width(w), height(h) {}
};

bool placeable(int a, int b, int c, int d)
{
	return (a < c && b < d) || (a < d && b < c);
}

int calMaxHeight(const vector<Cube> &vcCube)
{
	vector<int> viHeight;
	for (auto iter = vcCube.begin(); iter != vcCube.end(); iter++)
	{
		viHeight.push_back(iter->height);
	}
	bool bUpdate = true;
	while (bUpdate) {
		bUpdate = false;
		for (size_t i = 0; i < vcCube.size(); i++)
		{
			for (size_t j = 0; j < vcCube.size(); j++)
			{
				if (i == j) continue;
				if (placeable(vcCube[j].length, vcCube[j].width,
					vcCube[i].length, vcCube[i].width)) {
					if (viHeight[j] < viHeight[i] + vcCube[j].height) {
						viHeight[j] = viHeight[i] + vcCube[j].height;
						bUpdate = true;
					}
				}
			}
		}
	}
	int maxHeight = 0;
	for (size_t i = 0; i < viHeight.size(); i++)
	{
		if (viHeight[i] > maxHeight) {
			maxHeight = viHeight[i];
		}
	}
	return maxHeight;
}

int main()
{
	int Case = 0, n;
	while (cin >> n) {
		if (n == 0) break;
		vector<Cube> vcCube;
		int x, y, z;
		for (int i = 0; i < n; i++)
		{
			cin >> x >> y >> z;
			vcCube.push_back(Cube(x, y, z));
			vcCube.push_back(Cube(x, z, y));
			vcCube.push_back(Cube(y, z, x));
		}
		cout << "Case " << ++Case << ": maximum height = ";
		cout << calMaxHeight(vcCube) << endl;
	}
	return 0;
}
/*
1
10 20 30
2
6 8 10
5 5 5
7
1 1 1
2 2 2
3 3 3
4 4 4
5 5 5
6 6 6
7 7 7
5
31 41 59
26 53 58
97 93 23
84 62 64
33 83 27
0
*/
