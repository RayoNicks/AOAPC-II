#include <iostream>
#include <array>
#include <map>
#include <set>
#include <vector>

using namespace std;

#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

class Box
{
private:
	int x0, y0, z0;
	int x1, y1, z1;
public:
	int coordinate(size_t AxisIndex, bool start) const
	{
		if (AxisIndex == 0) return start ? x0 : x1;
		else if (AxisIndex == 1) return start ? y0 : y1;
		else if (AxisIndex == 2) return start ? z0 : z1;
		else return 0;
	}
	friend istream& operator >> (istream &is, Box &box)
	{
		is >> box.x0 >> box.y0 >> box.z0;
		is >> box.x1 >> box.y1 >> box.z1;
		box.x1 += box.x0;
		box.y1 += box.y0;
		box.z1 += box.z0;
		return is;
	}
};

class Axis
{
public:
	void SetAxis(const set<int> &points)
	{
		Points2No[*points.begin() - 1] = No2Points.size();
		No2Points.push_back(*points.begin() - 1);
		for (int point : points)
		{
			Points2No[point] = No2Points.size();
			No2Points.push_back(point);
		}
		Points2No[*points.rbegin() + 1] = No2Points.size();
		No2Points.push_back(*points.rbegin() + 1);
	}
	size_t Point2No(int point)
	{
		return Points2No[point];
	}
	int No2Point(size_t index)
	{
		return No2Points[index];
	}
	int size()
	{
		return static_cast<int>(No2Points.size() & 0x7FFFFFFF);
	}
	int length()
	{
		return No2Points.back() - No2Points.front();
	}
private:
	vector<int> No2Points;
	map<int, size_t> Points2No;
};

class Sculpture
{
private:
	vector<bool> sculpture;
	array<Axis, 3> axes;
	int To3D(int x, int y, int z)
	{
		return x * axes.at(1).size() * axes.at(2).size() + y * axes.at(2).size() + z;
	}
	void SetSculpture(int x, int y, int z)
	{
		sculpture[To3D(x, y, z)] = true;
	}
public:
	Sculpture(const vector<Box> &boxes)
	{
		array<set<int>, 3> AllPoints;
		for (const Box & box : boxes)
		{
			for (size_t AxisIndex = AXIS_X; AxisIndex <= AXIS_Z; AxisIndex++)
			{
				AllPoints.at(AxisIndex).insert(box.coordinate(AxisIndex, true));
				AllPoints.at(AxisIndex).insert(box.coordinate(AxisIndex, false));
			}
		}

		size_t TotalPoints = 1;
		for (size_t AxisIndex = AXIS_X; AxisIndex <= AXIS_Z; AxisIndex++)
		{
			axes.at(AxisIndex).SetAxis(AllPoints.at(AxisIndex));
			TotalPoints *= axes.at(AxisIndex).size();
		}
		sculpture.resize(TotalPoints, false);

		for (const Box& box : boxes)
		{
			array<array<size_t, 2>, 3> endpoints;
			for (size_t AxisIndex = AXIS_X; AxisIndex <= AXIS_Z; AxisIndex++)
			{
				endpoints.at(AxisIndex).at(0) = axes.at(AxisIndex).Point2No(box.coordinate(AxisIndex, true));
				endpoints.at(AxisIndex).at(1) = axes.at(AxisIndex).Point2No(box.coordinate(AxisIndex, false));
			}
			for (size_t x = endpoints.at(AXIS_X).at(0); x < endpoints.at(AXIS_X).at(1); x++)
			{
				for (size_t y = endpoints.at(AXIS_Y).at(0); y < endpoints.at(AXIS_Y).at(1); y++)
				{
					for (size_t z = endpoints.at(AXIS_Z).at(0); z < endpoints.at(AXIS_Z).at(1); z++)
					{
						SetSculpture(x, y, z);
					}
				}
			}
		}
	}
	int AirVolumn(int x, int y, int z)
	{
		int volumn = 1;
		array<int, 3> position{ x, y, z };
		for (size_t AxisIndex = AXIS_X; AxisIndex <= AXIS_Z; AxisIndex++)
		{
			volumn *= axes.at(AxisIndex).No2Point(position.at(AxisIndex) + 1) - axes.at(AxisIndex).No2Point(position.at(AxisIndex));
		}
		return volumn;
	}
	bool InsideSculpture(int x, int y, int z)
	{
		return x >= 0 && x < axes.at(0).size() - 1
			&& y >= 0 && y < axes.at(1).size() - 1
			&& z >= 0 && z < axes.at(2).size() - 1;
	}
	bool IsAir(int x, int y, int z)
	{
		return !sculpture[To3D(x, y, z)];
	}
	int BoxArea(size_t NormalVectorIndex, int after, int before)
	{
		int AfterIndex = (NormalVectorIndex + 1) % 3, BeforeIndex = (NormalVectorIndex + 2) % 3;
		return (axes.at(AfterIndex).No2Point(after + 1) - axes.at(AfterIndex).No2Point(after))
			* (axes.at(BeforeIndex).No2Point(before + 1) - axes.at(BeforeIndex).No2Point(before));
	}
	array<int, 3> size()
	{
		return{ axes.at(AXIS_X).size(), axes.at(AXIS_Y).size(), axes.at(AXIS_Z).size() };
	}
	int TotalVolumn()
	{
		int total = 1;
		for (size_t AxisIndex = AXIS_X; AxisIndex <= AXIS_Z; AxisIndex++)
		{
			total *= axes.at(AxisIndex).length();
		}
		return total;
	}
};

class Solution
{
public:
	Solution(const vector<Box> &boxes) : sculpture(boxes), AirVolumn(0), InnerArea(0)
	{
		array<int, 3> Size3D = sculpture.size();
		visited.resize(Size3D.at(AXIS_X), vector<vector<bool>>(Size3D.at(AXIS_Y), vector<bool>(Size3D.at(AXIS_Z), false)));
		FillAir(0, 0, 0);
	}
	int GetVolumn()
	{
		return sculpture.TotalVolumn() - AirVolumn;
	}
	int GetArea()
	{
		return InnerArea;
	}
private:
	Sculpture sculpture;
	vector<vector<vector<bool>>> visited;
	int AirVolumn, InnerArea;
	const vector<array<int, 3>> DirectVectors{ { 1, 0, 0 },{ -1, 0, 0 },{ 0, 1, 0 },{ 0, -1, 0 },{ 0, 0, 1 },{ 0, 0, -1 } };
	void FillAir(int currx, int curry, int currz)
	{
		visited[currx][curry][currz] = true;
		AirVolumn += sculpture.AirVolumn(currx, curry, currz);
		for (auto dv : DirectVectors)
		{
			int newx = currx + dv[0], newy = curry + dv[1], newz = currz + dv[2];
			if (sculpture.InsideSculpture(newx, newy, newz)) {
				if (sculpture.IsAir(newx, newy, newz)) {
					if (!visited[newx][newy][newz]) {
						FillAir(newx, newy, newz);
					}
				}
				else {
					if (dv[0] != 0) {
						InnerArea += sculpture.BoxArea(AXIS_X, curry, currz);
					}
					else if (dv[1] != 0) {
						InnerArea += sculpture.BoxArea(AXIS_Y, currz, currx);
					}
					else {
						InnerArea += sculpture.BoxArea(AXIS_Z, currx, curry);
					}
				}
			}
		}
	}
};

int main()
{
	int cases = 0;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		size_t n;
		vector<Box> boxes;
		Box box;
		cin >> n;
		for (size_t i = 0; i < n; i++)
		{
			cin >> box;
			boxes.push_back(box);
		}
		Solution solution(boxes);
		cout << solution.GetArea() << ' ' << solution.GetVolumn() << endl;
	}
	return 0;
}
/*
2
2
1 2 3 3 4 5
6 2 3 3 4 5
7
1 1 1 5 5 1
1 1 10 5 5 1
1 1 2 1 4 8
2 1 2 4 1 8
5 2 2 1 4 8
1 5 2 4 1 8
3 3 4 1 1 1
*/
