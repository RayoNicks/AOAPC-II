#include <iostream>
#include <array>
#include <deque>
#include <vector>

using namespace std;

struct Node
{
	int i, j;
	int k;
	int step;
	Node(int i, int j, int k, int step) : i(i), j(j), k(k), step(step) {}
};

class Solution
{
public:
	Solution(const vector<vector<char>> &grid, int m, int n, int k) : length(-1)
	{
		vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), -1));
		const vector<array<int, 2>> directions = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
		deque<Node> deq;
		deq.emplace_back(0, 0, k, 0);
		visited[0][0] = k;
		while (!deq.empty()) {
			Node curr = deq.front();
			deq.pop_front();
			if (curr.i == m - 1 && curr.j == n - 1) {
				length = curr.step;
				break;
			}
			for (const array<int, 2> &direction : directions)
			{
				Node next{ curr.i + direction[0], curr.j + direction[1], curr.k, curr.step + 1 };
				if (0 <= next.i && next.i < m && 0 <= next.j && next.j < n) {
					if (grid[next.i][next.j] == '0') {
						next.k = k;
					}
					else {
						next.k--;
						if (next.k < 0) continue;
					}
					if (visited[next.i][next.j] == -1 || visited[next.i][next.j] < next.k) {
						visited[next.i][next.j] = next.k;
						deq.push_back(next);
					}
				}
			}
		}
	}
	int FindShortestPathLength()
	{
		return length;
	}
private:
	int length;
};

int main()
{
	int cases = 0;
	cin >> cases;
	for (int c = 0; c < cases; c++)
	{
		int m, n, k;
		cin >> m >> n >> k;
		vector<vector<char>> grid(m, vector<char>(n, false));
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> grid[i][j];
			}
		}
		Solution solution(grid, m, n, k);
		cout << solution.FindShortestPathLength() << endl;
	}
	return 0;
}
/*
3
2 5
0
0 1 0 0 0
0 0 0 1 0
4 6
1
0 1 1 0 0 0
0 0 1 0 1 1
0 1 1 1 1 0
0 1 1 1 0 0
2 2
0
0 1
1 0
*/
