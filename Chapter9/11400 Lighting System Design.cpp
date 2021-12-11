#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Category
{
	int voltage;
	int SourceCost;
	int LampCost;
	int lamp;
	Category(const int v, const int sc, const int lc, const int l)
		:voltage(v), SourceCost(sc), LampCost(lc), lamp(l) {};
};

istream& operator >> (istream &is, Category &cate)
{
	is >> cate.voltage >> cate.SourceCost >> cate.LampCost >> cate.lamp;
	return is;
}

bool operator<(const Category &cate1, const Category &cate2)
{
	//升序排列
	return cate1.voltage > cate2.voltage;
}

bool replaceable(const Category &cate1, const Category &cate2)
{
	//判断i是否可以被j替换，其实没什么用
	if (cate2.LampCost <= cate1.LampCost) return true;
	else {
		if ((cate2.LampCost - cate1.LampCost) * cate1.lamp <= cate1.SourceCost) {
			return true;
		}
		else return false;
	}
}

void findMinimumCost(const vector<Category> &vCate)
{
	vector<vector<int>> Cost(vCate.size(), vector<int>(vCate.size(), INT_MAX));
	vector<int> sum(1, vCate[0].lamp);
	vector<size_t> IdxMin(vCate.size(), 0);
	Cost[0][0] = vCate[0].SourceCost + vCate[0].LampCost * vCate[0].lamp;
	for (size_t i = 1; i < vCate.size(); i++)
	{
		sum.push_back(sum.back() + vCate[i].lamp);
		Cost[i][0] = vCate[0].SourceCost + vCate[0].LampCost * sum[i];
		for (size_t j = 1; j <= i; j++)
		{
			Cost[i][j] = Cost[j - 1][IdxMin[j - 1]] + vCate[j].SourceCost + vCate[j].LampCost * (sum[i] - sum[j - 1]);
			if (Cost[i][j] < Cost[i][IdxMin[i]]) {
				IdxMin[i] = j;
			}
		}
	}
	cout << Cost.back()[IdxMin.back()] << endl;
}

int main()
{
	int n;
	while (cin >> n) {
		if (n == 0) break;
		vector<Category> vCategory(n, Category(0, 0, 0, 0));
		for (int i = 0; i < n; i++)
		{
			cin >> vCategory[i];
		}
		sort(vCategory.begin(), vCategory.end());
		findMinimumCost(vCategory);
	}
	return 0;
}
/*
3
100 500 10 20
120 600 8 16
220 400 7 18
0
*/
