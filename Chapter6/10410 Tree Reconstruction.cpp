#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<size_t> &bfs, const vector<size_t> &dfs) : tree(bfs.size() + 1)
	{
		reconstruct(bfs, dfs);
	}
	void print(ostream &os)
	{
		for (size_t i = 1; i < tree.size(); i++)
		{
			os << i << ':';
			for (size_t child : tree[i])
			{
				os << ' ' << child;
			}
			os << '\n';
		}
	}
private:
	vector<size_t> bfs, dfs;
	vector<vector<size_t>> tree;
	void reconstruct(const vector<size_t> &bfs, const vector<size_t> &dfs)
	{
		if (dfs.size() == 1) return;
		if (dfs.size() == 2) {
			tree[dfs[0]].push_back(dfs[1]);
			return;
		}
		vector<size_t> children;
		size_t root = dfs.front(), DfsIndex = 2;
		size_t ChildIndex = FindIndex(bfs, dfs[1]), PreIndex = ChildIndex, GrandIndex;
		while (1) {
			GrandIndex = FindIndex(bfs, dfs[DfsIndex]);
			if (PreIndex + 1 != GrandIndex || bfs[PreIndex] > bfs[GrandIndex]) break;
			if (++DfsIndex >= dfs.size()) {
				GrandIndex++;
				break;
			}
			PreIndex = GrandIndex;
		}
		for (size_t i = ChildIndex; i < GrandIndex; i++)
		{
			if (FindIndex(dfs, bfs[i]) != dfs.size()) {
				children.push_back(bfs[i]);
				tree[root].push_back(bfs[i]);
			}
		}
		vector<size_t>::const_iterator begin = find(dfs.begin(), dfs.end(), children[0]), end;
		for (size_t i = 1; i < children.size(); i++)
		{
			end = find(dfs.begin(), dfs.end(), children[i]);
			reconstruct(bfs, vector<size_t>(begin, end));
			begin = end;
		}
		reconstruct(bfs, vector<size_t>(begin, dfs.end()));
	}
	size_t FindIndex(const vector<size_t> &bfs, size_t target)
	{
		for (size_t i = 0; i < bfs.size(); i++)
		{
			if (bfs[i] == target) return i;
		}
		return bfs.size();
	}
};

int main()
{
	size_t n = 0;
	while (cin >> n) {
		vector<size_t> bfs, dfs;
		size_t num = 0;
		for (size_t i = 0; i < n; i++)
		{
			cin >> num;
			bfs.push_back(num);
		}
		for (size_t i = 0; i < n; i++)
		{
			cin >> num;
			dfs.push_back(num);
		}
		Solution solution(bfs, dfs);
		solution.print(cout);
	}
	return 0;
}
/*
8
4 3 5 1 2 8 7 6
4 3 1 7 2 6 5 8
*/
