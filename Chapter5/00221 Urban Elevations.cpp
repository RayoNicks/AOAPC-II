#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Building
{
	int no;
	double left, right, up, down;
	double height;
	bool visiable;
	Building(int no) : no(no)
	{
		visiable = false;
	}
	bool LineThroughBuilding(double x) const
	{
		return left < x && x < right;
	}
};

istream& operator>>(istream &is, Building &building)
{
	double width, depth;
	is >> building.left >> building.down;
	is >> width >> depth;
	building.right = building.left + width;
	building.up = building.down + depth;
	is >> building.height;
	return is;
}

void DetectVisiblility(vector<Building> &buildings, const vector<double> &interval)
{
	sort(buildings.begin(), buildings.end(), [](const Building &b1, const Building &b2)
	{
		if (b1.down < b2.down) return true;
		else if (b1.down > b2.down) return false;
		else return b1.left < b2.left;
	});
	for (size_t i = 0; i < interval.size() - 1; i++)
	{
		double midx = (interval[i] + interval[i + 1]) / 2.0;
		double CurrentHeight = 0.0;
		for (Building &building : buildings)
		{
			if (building.LineThroughBuilding(midx)) {
				if (!building.visiable) {
					building.visiable = CurrentHeight < building.height;
				}
				CurrentHeight = max(CurrentHeight, building.height);
			}
		}
	}
	sort(buildings.begin(), buildings.end(), [](const Building &b1, const Building &b2)
	{
		if (b1.left < b2.left) return true;
		else if (b1.left > b2.left) return false;
		else return b1.down < b2.down;
	});
	size_t i = 0;
	for (; i < buildings.size(); i++)
	{
		if (buildings[i].visiable) {
			cout << buildings[i++].no;
			break;
		}
	}
	for (; i < buildings.size(); i++)
	{
		if (buildings[i].visiable) {
			cout << ' ' << buildings[i].no;
		}
	}
	cout << endl;
}

int main()
{
	int n = 0, MapNumber = 1;
	while (cin >> n) {
		if (n == 0) break;
		if (MapNumber != 1) cout << endl;
		vector<Building> buildings;
		set<double> points;
		for (int i = 0; i < n; i++)
		{
			Building building(i + 1);
			cin >> building;
			buildings.push_back(building);
			points.insert(building.left);
			points.insert(building.right);
		}
		vector<double> interval(points.size());
		copy(points.begin(), points.end(), interval.begin());
		cout << "For map #" << MapNumber++ << ", the visible buildings are numbered as follows:" << endl;
		DetectVisiblility(buildings, interval);
	}
	return 0;
}
/*
14
160 0 30 60 30
125 0 32 28 60
95 0 27 28 40
70 35 19 55 90
0 0 60 35 80
0 40 29 20 60
35 40 25 45 80
0 67 25 20 50
0 92 90 20 80
95 38 55 12 50
95 60 60 13 30
95 80 45 25 50
165 65 15 15 25
165 85 10 15 35
0
*/
