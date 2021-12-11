#include <iostream>
#include <vector>
#include <array>
#include <iomanip>
#include <cmath>
#include <cfloat>

#define EPS 1e-6

using namespace std;

struct Point
{
	int x, y;
	Point(const int x, const int y) : x(x), y(y) {}
};

bool operator<(const Point &p1, const Point &p2)
{
	return p1.x < p2.x;
}

double calDistance(const Point &p1, const Point &p2)
{
	double x = (double)(p1.x - p2.x);
	double y = (double)(p1.y - p2.y);
	return sqrt(x * x + y * y);
}

void findShortestTour(const vector<Point> &vecPoint)
{
	const size_t points = vecPoint.size();
	vector<vector<double>> distance(points, vector<double>(points, DBL_MAX));
	double go, back;
	distance[1][0] = calDistance(vecPoint[0], vecPoint[1]);
	for (size_t i = 1; i < points - 1; i++)
	{
		go = calDistance(vecPoint[i], vecPoint[i + 1]);
		for (size_t j = 0; j < i; j++)
		{
			back = calDistance(vecPoint[j], vecPoint[i + 1]);
			if (distance[i + 1][j] > distance[i][j] + go + EPS) {
				distance[i + 1][j] = distance[i][j] + go;
			}
			if (distance[i + 1][i] > distance[i][j] + back + EPS) {
				distance[i + 1][i] = distance[i][j] + back;
			}
		}
	}
	for (size_t j = 0; j < points - 1; j++)
	{
		back = calDistance(vecPoint[j], vecPoint.back());
		if (distance[points - 1][points - 1] > distance[points - 1][j] + back + EPS) {
			distance[points - 1][points - 1] = distance[points - 1][j] + back;
		}
	}
	cout << fixed << setprecision(2) <<distance[points - 1][points - 1] << endl;
}

int main()
{
	int number;
	while (cin >> number) {
		vector<Point> vecPoint;
		int x, y;
		for (int i = 0; i < number; i++)
		{
			cin >> x >> y;
			vecPoint.push_back(Point(x, y));
		}
		findShortestTour(vecPoint);
	}
	return 0;
}
/*
3
1 1
2 3
3 1
4
1 1
2 3
3 1
4 2
*/
