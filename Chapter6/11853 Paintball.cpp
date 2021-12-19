#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

struct Opponent
{
	double x, y, r;
	bool cross(const Opponent &opponent) const
	{
		return pow(x - opponent.x, 2) + pow(y - opponent.y, 2)
			< pow(r + opponent.r, 2);
	}
};

struct Block
{
	vector<Opponent> opponents;
	double NorthBound, SouthBound;
	Block(const Opponent &opponent)
	{
		NorthBound = opponent.y + opponent.r;
		SouthBound = opponent.y - opponent.r;
		opponents.push_back(opponent);
	}
	void AddOpponent(const Opponent &opponent)
	{
		NorthBound = max(opponent.y + opponent.r, NorthBound);
		SouthBound = min(opponent.y - opponent.r, SouthBound);
		opponents.push_back(opponent);
	}
};

class Solution
{
public:
	Solution(const vector<Opponent> &opponents) : visited(opponents.size(), false)
	{
		for (size_t i = 0; i < opponents.size(); i++)
		{
			if (!visited[i]) {
				visited[i] = true;
				blocks.push_back(Block(opponents[i]));
				CountBlock(i, opponents);
			}
		}
	}
	string GetEntry()
	{
		double LeftY = 1000.0, RightY = 1000.0, y;
		ostringstream oss;
		for (const Block &block : blocks)
		{
			if (block.NorthBound > 1000.0) {
				if (block.SouthBound < 0.0) return "IMPOSSIBLE";
				else {
					for (const Opponent &opponent : block.opponents)
					{
						if (opponent.x - opponent.r < 0.0) {
							y = opponent.y - sqrt((pow(opponent.r, 2) - pow(opponent.x, 2)));
							LeftY = min(y, LeftY);
						}
						if (opponent.x + opponent.r > 1000.0) {
							y = opponent.y - sqrt((pow(opponent.r, 2) - pow(1000.0 - opponent.x, 2)));
							RightY = min(y, RightY);
						}
					}
				}
			}
		}
		oss << fixed << setprecision(2);
		oss << "0.00 " << LeftY << ' ' << "1000.00 " << RightY;
		return oss.str();
	}
private:
	vector<Block> blocks;
	vector<bool> visited;
	void CountBlock(size_t curr, const vector<Opponent> &opponents)
	{
		for (size_t i = 0; i < opponents.size(); i++)
		{
			if (!visited[i] && opponents[curr].cross(opponents[i])) {
				visited[i] = true;
				blocks.back().AddOpponent(opponents[i]);
				CountBlock(i, opponents);
			}
		}
	}
};

int main()
{
	size_t n = 0;
	while (cin >> n) {
		vector<Opponent> opponents;
		for (size_t i = 0; i < n; i++)
		{
			Opponent opponent;
			cin >> opponent.x >> opponent.y >> opponent.r;
			opponents.push_back(opponent);
		}
		Solution solution(opponents);
		cout << solution.GetEntry() << endl;
	}
	return 0;
}
/*
3
500 500 499
0 0 999
1000 1000 200
*/
