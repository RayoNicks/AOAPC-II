#include <iostream>
#include <algorithm>
#include <climits>
#include <deque>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<map<size_t, size_t>> &rooms) 
		: graph(rooms), levels(rooms.size(), UINT_MAX), visited(rooms.size(), false)
	{
		SearchIdealPath();
	}
	void print(ostream &os)
	{
		os << IdealPath.size() << endl;
		cout << IdealPath.front();
		for(size_t i = 1; i < IdealPath.size(); i++)
		{
			cout << ' ' << IdealPath[i];
		}
		cout << endl;
	}
private:
	const vector<map<size_t, size_t>> &graph;
	vector<size_t> levels, IdealPath;
	vector<bool> visited;
	void SearchIdealPath()
	{
		deque<size_t> q;
		visited.back() = true;
		q.push_back(graph.size() - 1);
		levels.back() = 0;
		while (!q.empty()) {
			size_t curr = q.front();
			q.pop_front();
			if (curr == 0) break;
			for (auto iter = graph[curr].begin(); iter != graph[curr].end(); iter++)
			{
				if (!visited[iter->first]) {
					visited[iter->first] = true;
					q.push_back(iter->first);
					levels[iter->first] = levels[curr] + 1;
				}
			}
		}
		set<size_t> SameColor{ 0 };
		while (1) {
			size_t MinColor = UINT_MAX;
			set<size_t> NextSameColor;
			for (size_t curr : SameColor)
			{
				for (auto iter = graph[curr].begin(); iter != graph[curr].end(); iter++)
				{
					if (levels[iter->first] == levels[curr] - 1) {
						if (iter->second < MinColor) {
							NextSameColor.clear();
							NextSameColor.insert(iter->first);
							MinColor = iter->second;
						}
						else if (iter->second == MinColor) {
							NextSameColor.insert(iter->first);
						}
					}
				}
			}
			IdealPath.push_back(MinColor);
			if (IdealPath.size() == levels.front()) break;
			SameColor = NextSameColor;
		}
	}
};

int main()
{
	size_t n, m;
	while (cin >> n) {
		cin >> m;
		vector<map<size_t, size_t>> rooms(n);
		for (size_t i = 0; i < m; i++)
		{
			size_t a, b, c;
			cin >> a >> b >> c;
			if (a == b) continue;
			auto iter = rooms[a - 1].find(b - 1);
			if (iter == rooms[a - 1].end()) {
				rooms[a - 1][b - 1] = c;
				rooms[b - 1][a - 1] = c;
			}
			else if(c < iter->second){
				iter->second = c;
				rooms[b - 1][a - 1] = c;
			}
		}
		Solution solution(rooms);
		solution.print(cout);
	}
	return 0;
}
/*
4 6
1 2 1
1 3 2
3 4 3
2 3 1
2 4 4
3 1 1
*/
