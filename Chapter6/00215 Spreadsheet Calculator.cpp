#include <iostream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Cell
{
	string index, expr;
	map<string, int> deps;
	int value = 0;
	bool evaluated = false;
	Cell() = default;
	Cell(size_t i, size_t j, const string& expr) : expr(expr)
	{
		index.push_back(static_cast<char>(i + 'A'));
		index.push_back(static_cast<char>(j + '0'));
		if (expr.front() == '-' || isdigit(expr.front())) {
			evaluated = true;
			value = stoi(expr);
		}
		else {
			evaluated = false;
			int times = 1;
			string item;
			string::const_iterator curr = expr.begin(), OperatorPosition;
			while (1) {
				OperatorPosition = find_if(curr, expr.end(), [](const char ch) { return ch == '+' || ch == '-'; });
				item.assign(curr, OperatorPosition);
				if (isdigit(*curr)) {
					int constant = stoi(item);
					if (times == 1) value += constant;
					else value -= constant;
				}
				else {
					deps[item] += times;
				}
				if (OperatorPosition != expr.end()) {
					curr = OperatorPosition + 1;
					if (*OperatorPosition == '+') times = 1;
					else times = -1;
				}
				else break;
			}
		}
	}
};

class Solution
{
public:
	Solution(const vector<vector<Cell>> &input) : sheet(input), visited(sheet.size(), vector<bool>(sheet[0].size(), false))
	{
		for (size_t i = 0; i < sheet.size(); i++)
		{
			for (size_t j = 0; j < sheet[i].size(); j++)
			{
				if (!sheet[i][j].evaluated && !visited[i][j]) {
					visited[i][j] = true;
					if (!evaluate(sheet[i][j])) {
						CircleReference.insert(make_pair(i, j));
					}
				}
			}
		}
	}
	void print(ostream& os)
	{
		if (!CircleReference.empty()) {
			for (const pair<size_t, size_t> &RowCol : CircleReference)
			{
				os << sheet[RowCol.first][RowCol.second].index << ": " << sheet[RowCol.first][RowCol.second].expr << '\n';
			}
		}
		else {
			os << ' ';
			for (size_t col = 0; col < sheet[0].size(); col++)
			{
				os << setw(6) << setfill(' ') << col;
			}
			os << '\n';
			for (size_t row = 0; row < sheet.size(); row++)
			{
				os << static_cast<char>('A' + row);
				for (size_t col = 0; col < sheet[row].size(); col++)
				{
					os << setw(6) << setfill(' ') << sheet[row][col].value;
				}
				os << '\n';
			}
		}
	}
private:
	vector<vector<Cell>> sheet;
	set<pair<size_t, size_t>> CircleReference;
	vector<vector<bool>> visited;
	bool evaluate(Cell &cell)
	{
		for (auto iter = cell.deps.begin(); iter != cell.deps.end(); iter++)
		{
			const string &DepIndex = iter->first;
			size_t DepRow = DepIndex[0] - 'A', DepCol = DepIndex[1] - '0';
			Cell& DepCell = sheet[DepRow][DepCol];
			if (DepCell.evaluated) {
				cell.value += iter->second * DepCell.value;
			}
			else if (!visited[DepRow][DepCol]) {
				visited[DepRow][DepCol] = true;
				if (evaluate(DepCell)) {
					cell.value += iter->second * DepCell.value;
				}
				else {
					CircleReference.insert(make_pair(DepRow, DepCol));
					return false;
				}
			}
			else return false;
		}
		cell.evaluated = true;
		return true;
	}
};

int main()
{
	size_t row, col;
	while (cin >> row >> col) {
		if (row == 0 && col == 0) break;
		vector<vector<Cell>> sheet(row);
		string expr;
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				cin >> expr;
				sheet[i].push_back(Cell(i, j, expr));
			}
		}
		Solution solution(sheet);
		solution.print(cout);
		cout << endl;
	}
}
/*
2 2
A1+B1
5
3
B0-A1
3 2
A0
5
C1
7
A1+B1
B0+A1
0 0
*/
