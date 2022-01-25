#include <iostream>
#include <array>
#include <deque>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Dice
{
	static const array<int, 7> opposite;
	static const vector<vector<int>> LeftRotation;
	int top, facing;
	Dice(int top, int facing) : top(top), facing(facing) {}
	void up()
	{
		int opp = opposite[top];
		top = facing;
		facing = opp;
	}
	void down()
	{
		int opp = opposite[facing];
		facing = top;
		top = opp;
	}
	void left()
	{
		top = LeftRotation[facing - 1][top - 1];
	}
	void right()
	{
		top = opposite[LeftRotation[facing - 1][top - 1]];
	}
	int state() const
	{
		return top * 10 + facing;
	}
};

const array<int, 7> Dice::opposite = { 0, 6, 5, 4, 3, 2 ,1 };

const vector<vector<int>> Dice::LeftRotation = {
	{ -1, 4, 2 ,5, 3, -1 },
	{ 3, -1, 6, 1, -1, 4 },
	{ 5, 1, -1, -1, 6, 2 },
	{ 2, 6, -1, -1, 1, 5 },
	{ 4, -1, 1, 6, -1, 3 },
	{ -1, 3, 5, 2, 4, -1 }
};

struct Node
{
	Dice dice;
	size_t row, col;
	vector<pair<size_t, size_t>> path;
	Node(const Dice &dice, size_t row, size_t col) : dice(dice), row(row), col(col)
	{
		path.push_back(make_pair(row, col));
	}
	void up()
	{
		dice.up();
		row--;
		path.push_back(make_pair(row, col));
	}
	void down()
	{
		dice.down();
		row++;
		path.push_back(make_pair(row, col));
	}
	void left()
	{
		dice.left();
		col--;
		path.push_back(make_pair(row, col));
	}
	void right()
	{
		dice.right();
		col++;
		path.push_back(make_pair(row, col));
	}
};

class Solution
{
public:
	Solution(const string &name, const vector<vector<int>> &maze, size_t StartRow, size_t StartCol, int top, int facing)
		: name(name), maze(maze), EndRow(StartRow), EndCol(StartCol), dice(top, facing),
		states(maze.size(), vector<set<int>>(maze[0].size()))
	{
		deque<Node> deq;
		deq.emplace_back(dice, StartRow, StartCol);
		while (!deq.empty()) {
			Node curr = deq.front();
			deq.pop_front();
			if (curr.path.size() != 1 && curr.row == EndRow && curr.col == EndCol) {
				path = curr.path;
				break;
			}
			if (curr.row > 0 && movable(curr.row - 1, curr.col, curr.dice)) {
				Node node = curr;
				node.up();
				if(!visiting(node)) {
					deq.push_back(node);
				}
			}
			if (curr.row + 1 < maze.size() && movable(curr.row + 1, curr.col, curr.dice)) {
				Node node = curr;
				node.down();
				if (!visiting(node)) {
					deq.push_back(node);
				}
			}
			if (curr.col > 0 && movable(curr.row, curr.col - 1, curr.dice)) {
				Node node = curr;
				node.left();
				if (!visiting(node)) {
					deq.push_back(node);
				}
			}
			if (curr.col + 1 < maze[0].size() && movable(curr.row, curr.col + 1, curr.dice)) {
				Node node = curr;
				node.right();
				if (!visiting(node)) {
					deq.push_back(node);
				}
			}
		}
	}
	void print(ostream &os)
	{
		os << name;
		if (path.empty()) {
			os << "\n  No Solution Possible";
		}
		else {
			for (size_t i = 0; i < path.size() - 1; i++)
			{
				if (i % 9 == 0) {
					os << "\n  ";
				}
				cout << '(' << path[i].first + 1 << ',' << path[i].second + 1 << "),";
			}
			cout << '(' << path.back().first + 1 << ',' << path.back().second + 1 << ")";
		}
		os << endl;
	}
private:
	string name;
	vector<vector<int>> maze;
	size_t EndRow, EndCol;
	Dice dice;
	vector<vector<set<int>>> states;
	vector<pair<size_t, size_t>> path;
	bool movable(size_t row, size_t col, const Dice &dice)
	{
		return maze[row][col] == -1 || maze[row][col] == dice.top;
	}
	bool visiting(const Node &node)
	{
		set<int> &state = states[node.row][node.col];
		bool found = state.find(node.dice.state()) != state.end();
		state.insert(node.dice.state());
		return found;
	}
};

int main()
{
	string name;
	while (cin >> name) {
		if (name == "END") break;
		size_t row, col, sr, sc;
		int top, facing;
		cin >> row >> col >> sr >> sc >> top >> facing;
		vector<vector<int>> maze(row, vector<int>(col, 0));
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				cin >> maze[i][j];
			}
		}
		Solution solution(name, maze, sr - 1, sc - 1, top, facing);
		solution.print(cout);
	}
	return 0;
}
/*
DICEMAZE1
3 3 1 2 5 1
-1 2 4
5 5 6
6 -1 -1
DICEMAZE2
4 7 2 6 3 6
6 4 6 0 2 6 4
1 2 -1 5 3 6 1
5 3 4 5 6 4 2
4 1 2 0 3 -1 6
DICEMAZE3
3 3 1 1 2 4
2 2 3
4 5 6
-1 -1 -1
END
*/
