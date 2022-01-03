#include <iostream>
#include <array>
#include <deque>
#include <string>
#include <vector>

using namespace std;

struct Node
{
	int row, col;
	size_t step;
	Node(int r, int c, size_t step) : row(r),col(c), step(step){}
};

class Solution
{
public:
	Solution(const string &start, const string &end)
		: board(8, vector<bool>(8, false)), shortest(0)
	{
		StartCol = start[0] - 'a';
		StartRow = start[1] - '1';
		EndCol = end[0] - 'a';
		EndRow = end[1] - '1';
		FindShortestPathLength();
	}
	int ShortestPathLength()
	{
		return shortest;
	}
private:
	vector<vector<bool>> board;
	int StartRow, StartCol, EndRow, EndCol;
	int shortest;
	bool onBoard(int row, int col)
	{
		return 0 <= row && row < 8 && 0 <= col && col < 8;
	}
	void FindShortestPathLength()
	{
		const vector<array<int, 2>> directions = {
			{ 1, 2 }, { -1, 2 },
			{ 2, -1 }, { 2, 1 },
			{ -1, -2 }, { 1, -2 },
			{ -2, -1 }, { -2, 1 } };
		board[StartRow][StartCol] = true;
		deque<Node> deq;
		deq.emplace_back(StartRow, StartCol, 0);
		while (!deq.empty()) {
			auto curr = deq.front();
			deq.pop_front();
			if (curr.row == EndRow && curr.col == EndCol) {
				shortest = curr.step;
				break;
			}
			for (const array<int, 2> &dir : directions)
			{
				Node node{ curr.row + dir[0],curr.col + dir[1], curr.step + 1 };
				if (onBoard(node.row, node.col) && !board[node.row][node.col]) {
					board[node.row][node.col] = true;
					deq.push_back(node);
				}
			}
		}
	}
};

int main()
{
	string start, end;
	while (cin >> start >> end) {
		Solution solution(start, end);
		cout << "To get from " << start << " to " << end << " takes "
			<< solution.ShortestPathLength() << " knight moves." << endl;
	}
	return 0;
}
/*
e2 e4
a1 b2
b2 c3
a1 h8
a1 h7
h8 a1
b1 c3
f6 f6
*/
