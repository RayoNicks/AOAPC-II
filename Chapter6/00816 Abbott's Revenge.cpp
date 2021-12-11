#include <iostream>
#include <array>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Location
{
	vector<pair<size_t, size_t>> WalkingThrough;
	size_t x, y;
	char direction;
	Location() = default;
	Location(size_t x, size_t y, char direction) : x(x), y(y), direction(direction) {};
	bool operator<(const Location &location) const
	{
		if (x != location.x) return x < location.x;
		else if (y != location.y) return y < location.y;
		else return direction < location.direction;
	}
};

struct Sign
{
	map<char, vector<Location>> signs;
	void BuildSign(stringstream &ss, size_t x, size_t y)
	{
		string group;
		while (ss >> group) {
			if (group == "*") break;
			char direction = group[0];
			for (size_t i = 1; i < group.size(); i++)
			{
				switch (direction)
				{
				case 'N':
					if (group.at(i) == 'L') signs[direction].emplace_back(x, y - 1, 'W');
					else if(group.at(i) == 'F') signs[direction].emplace_back(x - 1, y, 'N');
					else signs[direction].emplace_back(x, y + 1, 'E');
					break;
				case 'S':
					if (group.at(i) == 'L') signs[direction].emplace_back(x, y + 1, 'E');
					else if (group.at(i) == 'F') signs[direction].emplace_back(x + 1, y, 'S');
					else signs[direction].emplace_back(x, y - 1, 'W');
					break;
				case 'W':
					if (group.at(i) == 'L') signs[direction].emplace_back(x + 1, y, 'S');
					else if (group.at(i) == 'F') signs[direction].emplace_back(x, y - 1, 'W');
					else signs[direction].emplace_back(x - 1, y, 'N');
					break;
				case 'E':
					if (group.at(i) == 'L') signs[direction].emplace_back(x - 1, y, 'N');
					else if (group.at(i) == 'F') signs[direction].emplace_back(x, y + 1, 'E');
					else signs[direction].emplace_back(x + 1, y, 'S');
					break;
				}
			}
		}
	}
};

class Solution
{
public:
	Solution(const string &name, istream &is) : name(name)
	{
		is >> StartX >> StartY >> StartDirection >> EndX >> EndY;
		is.get();
		string line;
		while (getline(is, line)) {
			if (line == "0") break;
			stringstream ss(line);
			size_t x, y;
			ss >> x >> y;
			maze[x][y].BuildSign(ss, x, y);
		}
	}
	void solve()
	{
		Location curr(StartX, StartY, StartDirection);
		curr.WalkingThrough.push_back(make_pair(StartX, StartY));
		if (StartDirection == 'N') curr.x--;
		else if (StartDirection == 'S') curr.x++;
		else if (StartDirection == 'W') curr.y--;
		else curr.y++;
		curr.WalkingThrough.push_back(make_pair(curr.x, curr.y));
		queue<Location> nodes;
		nodes.push(curr);
		locations.insert(curr);
		while (!nodes.empty()) {
			curr = nodes.front();
			nodes.pop();
			if (curr.x == EndX && curr.y == EndY) {
				path = curr.WalkingThrough;
				break;
			}
			const Sign &sign = maze[curr.x][curr.y];
			if (sign.signs.empty()) continue;
			const vector<Location> &arrows = sign.signs.at(curr.direction);
			for (auto node : arrows)
			{
				if (locations.find(node) == locations.end()) {
					locations.insert(node);
					node.WalkingThrough = curr.WalkingThrough;
					node.WalkingThrough.push_back(make_pair(node.x, node.y));
					nodes.push(node);
				}
			}
		}
	}
	string name;
	vector<pair<size_t, size_t>> path;
private:
	array<array<Sign, 10>, 10> maze;
	size_t StartX, StartY, EndX, EndY;
	char StartDirection;
	set<Location> locations;
};

ostream& operator<<(ostream &os, const Solution &solution)
{
	os << solution.name << "\n ";
	if (solution.path.empty()) os << " No Solution Possible";
	else {
		size_t count = 0;
		for (size_t i = 0; i < solution.path.size(); i++)
		{
			os << " (" << solution.path[i].first << ',' << solution.path[i].second << ')';
			if (++count == 10) {
				count = 0;
				if(i + 1 < solution.path.size()) os << "\n ";
			}
		}
	}
	return os;
}

int main()
{
	string name;
	while (cin >> name) {
		if (name == "END") break;
		Solution solution(name, cin);
		solution.solve();
		cout << solution << endl;
	}
	return 0;
}
/*
SAMPLE
3 1 N 3 3
1 1 WL NR *
1 2 WLF NR ER *
1 3 NL ER *
2 1 SL WR NF *
2 2 SL WF ELF *
2 3 SFR EL *
0
NOSOLUTION
3 1 N 3 2
1 1 WL NR *
1 2 NL ER *
2 1 SL WR NFR *
2 2 SR EL *
0
END
*/
