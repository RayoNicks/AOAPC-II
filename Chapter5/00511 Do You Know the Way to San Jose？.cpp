#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

#define EPS 1E-6

using namespace std;

struct Location
{
	string name;
	double x, y;
};

istream &operator >> (istream &is, Location &location)
{
	is >> location.x >> location.y;
	return is;
}

struct Map
{
	string name;
	double left, up, right, down;
	double area() const
	{
		return (right - left) * (up - down);
	}
	bool SameDetailLevel(const Map &map) const
	{
		return abs(area() - map.area()) < EPS;
	}
	bool included(const Location &location) const
	{
		return left <= location.x && location.x <= right
			&& down <= location.y && location.y <= up;
	}
};

istream &operator >> (istream &is, Map &map)
{
	is >> map.left >> map.up >> map.right >> map.down;
	if (map.left > map.right) swap(map.left, map.right);
	if (map.down > map.up) swap(map.down, map.up);
	return is;
}

struct Request
{
	string name;
	size_t level;
};

void ReadMap(vector<Map> &maps)
{
	string word;
	cin >> word;
	while (1) {
		maps.push_back(Map());
		cin >> maps.back().name;
		if (maps.back().name == "LOCATIONS") {
			maps.pop_back();
			break;
		}
		else {
			cin >> maps.back();
		}
	}
}

void ReadLocation(vector<Location> &locations)
{
	while (1) {
		locations.push_back(Location());
		cin >> locations.back().name;
		if (locations.back().name == "REQUESTS") {
			locations.pop_back();
			break;
		}
		else {
			cin >> locations.back();
		}
	}
}

bool MoreDetailed(const Location &location, const Map &m1, const Map &m2)
{
	double center1 = pow(location.x - (m1.left + m1.right) / 2.0, 2) + pow(location.y - (m1.down + m1.up) / 2.0, 2);
	double center2 = pow(location.x - (m2.left + m2.right) / 2.0, 2) + pow(location.y - (m2.down + m2.up) / 2.0, 2);
	if (center1 < center2) return true;
	else if (center1 > center2) return false;
	else;

	double ratio1 = abs((m1.up - m1.down) / (m1.right - m1.left) - 0.75);
	double ratio2 = abs((m2.up - m2.down) / (m2.right - m2.left) - 0.75);
	if (ratio1 < ratio2) return true;
	else if (ratio1 > ratio2) return false;
	else;

	double corner1 = pow(location.x - m1.left, 2) + pow(location.y - m1.down, 2);
	double corner2 = pow(location.x - m2.left, 2) + pow(location.y - m2.down, 2);
	if (corner1 > corner2) return true;
	else if (corner1 < corner2) return false;
	else;

	return m1.left < m2.left;
}

void OutputMap(const vector<Map> &maps, const vector<Location> &locations, const Request &request)
{
	cout << request.name << " at detail level " << request.level << ' ';
	auto LocIter = find_if(locations.begin(), locations.end(), [&request](const Location &location)
	{
		return request.name == location.name;
	});
	if (LocIter != locations.end()) {
		vector<Map> included;
		for (auto MapIter = maps.begin(); MapIter != maps.end(); MapIter++)
		{
			if (MapIter->included(*LocIter)) {
				auto SameDetailLevelIter = find_if(included.begin(), included.end(), [&MapIter](const Map &map)
				{
					return map.SameDetailLevel(*MapIter);
				});
				if (SameDetailLevelIter != included.end()) {
					if (MoreDetailed(*LocIter, *MapIter, *SameDetailLevelIter)) {
						*SameDetailLevelIter = *MapIter;
					}
				}
				else {
					included.push_back(*MapIter);
				}
			}
		}
		if (included.empty()) {
			cout << "no map contains that location" << endl;
		}
		else {
			sort(included.begin(), included.end(), [](const Map &m1, const Map &m2)
			{
				return m1.area() > m2.area();
			});
			if (request.level <= included.size()) {
				cout << "using " << included[request.level - 1].name << endl;
			}
			else {
				cout << "no map at that detail level; using " << included.back().name << endl;
			}
		}
	}
	else {
		cout << "unknown location" << endl;
	}
}

int main()
{
	vector<Map> maps;
	vector<Location> locations;
	ReadMap(maps);
	ReadLocation(locations);
	Request request;
	while (cin >> request.name) {
		if (request.name == "END") break;
		cin >> request.level;
		OutputMap(maps, locations, request);
	}
	return 0;
}
/*
MAPS
BayArea -6.0 12.0 -11.0 5.0
SantaClara 4.0 9.0 -3.5 2.5
SanJoseRegion -3.0 10.0 11.0 3.0
CenterCoast -5.0 11.0 1.0 -8.0
SanMateo -5.5 4.0 -12.5 9.0
NCalif -13.0 -7.0 13.0 15.0
LOCATIONS
Monterey -4.0 2.0
SanJose -1.0 7.5
Fresno 7.0 0.1
SanFrancisco -10.0 8.6
SantaCruz -4.0 2.0
SanDiego 13.8 -19.3
REQUESTS
SanJose 3
SanFrancisco 2
Fresno 2
Stockton 1
SanDiego 2
SanJose 4
SantaCruz 3
END
*/
