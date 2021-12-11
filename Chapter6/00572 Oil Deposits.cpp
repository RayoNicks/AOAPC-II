#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(size_t m, size_t n, istream &is)
		: grid(vector<vector<char>>(m, vector<char>(n))),
		visited(vector<vector<bool>>(m, vector<bool>(n, false)))
	{
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				is >> grid[i][j];
			}
		}
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if (grid[i][j] == '@' && !visited[i][j]) {
					CountOilDeposits(i, j);
					OilDeposits++;
				}
			}
		}
	};
	int OilDeposits = 0;
private:
	vector<vector<char>> grid;
	vector<vector<bool>> visited;
	void CountOilDeposits(size_t i, size_t j)
	{
		if (grid[i][j] != '@' || visited[i][j]) return;
		visited[i][j] = true;
		if (i > 0) {
			if (j > 0) {
				CountOilDeposits(i - 1, j - 1);
			}
			CountOilDeposits(i - 1, j);
			if (j + 1 < grid[i].size()) {
				CountOilDeposits(i - 1, j + 1);
			}
		}
		if (j > 0) {
			CountOilDeposits(i, j - 1);
		}
		if (j + 1 < grid[i].size()) {
			CountOilDeposits(i, j + 1);
		}
		if (i + 1 < grid.size()) {
			if (j > 0) {
				CountOilDeposits(i + 1, j - 1);
			}
			CountOilDeposits(i + 1, j);
			if (j + 1 < grid[i].size()) {
				CountOilDeposits(i + 1, j + 1);
			}
		}
	}
};

int main()
{
	size_t m, n;
	while (cin >> m >> n) {
		if (m == 0 && n == 0) break;
		Solution solution(m, n, cin);
		cout << solution.OilDeposits << endl;
	}
	return 0;
}
/*
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0
*/
