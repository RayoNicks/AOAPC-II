#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<string> &file) : tree(file)
	{
		undrawed.push_back('(');
		if (tree.size() != 0) {
			for (size_t i = 0; i < tree[0].length(); i++)
			{
				if (IsNodeName(tree[0][i])) {
					undraw(0, i);
					break;
				}
			}
		}
		undrawed.push_back(')');
	}
	void print(ostream &os)
	{
		os << undrawed << endl;
	}
private:
	vector<string> tree;
	string undrawed;
	void undraw(size_t row, size_t col)
	{
		undrawed.push_back(tree[row][col]);
		undrawed.push_back('(');
		size_t ChlidLeft = col + 1, ChildRight = col;
		if (row + 3 < tree.size() && tree[row + 1][col] == '|') {
			while (ChlidLeft > 0 && tree[row + 2][ChlidLeft - 1] == '-') ChlidLeft--;
			while (ChildRight < tree[row + 2].length() && tree[row + 2][ChildRight] == '-') ChildRight++;
			for (size_t i = ChlidLeft; i < tree[row + 3].length() && i < ChildRight; i++)
			{
				if (IsNodeName(tree[row + 3][i])) {
					undraw(row + 3, i);
				}
			}
		}
		undrawed.push_back(')');
	}
	inline bool IsNodeName(char c)
	{
		return c != '|' && c != '-' && c != ' ' && c != '#';
	}
};

int main()
{
	int T;
	cin >> T;
	cin.get();
	for (int t = 0; t < T; t++)
	{
		vector<string> file;
		string line;
		while (getline(cin, line)) {
			if (line == "#") break;
			file.push_back(line);
		}
		Solution solution(file);
		solution.print(cout);
	}
	return 0;
}
/*
2
   A
   |
--------
B  C   D
   |   |
 ----- -
 E   F G
#
e
|
----
f g
#
*/
