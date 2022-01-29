#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const vector<vector<bool>>& graph, size_t E, size_t T) : graph(graph), visited(graph.size(), false), edges(E), time(T)
	{
		CountSubgraph();
		for (const vector<size_t>& subgraph : subgraphs)
		{
			size_t n = CountVertexWithOddDegree(subgraph);
			if (n > 2) edges += (n - 2) / 2;
		}
		edges += subgraphs.empty() ? 0 : subgraphs.size() - 1;
		time *= edges;
	}
	size_t TotalTraverseTime()
	{
		return time;
	}
private:
	vector<vector<bool>> graph;
	vector<bool> visited;
	vector<vector<size_t>> subgraphs;
	size_t edges, time;
	void CountSubgraph()
	{
		for (size_t i = 0; i < graph.size(); i++)
		{
			if (!visited[i]) {
				visited[i] = true;
				subgraphs.push_back(vector<size_t>());
				subgraphs.back().push_back(i);
				dfs(i, subgraphs.back());
				if (subgraphs.back().size() == 1) {
					subgraphs.pop_back();
				}
			}
		}
	}
	void dfs(size_t curr, vector<size_t> &subgraph)
	{
		for (size_t adj = 0; adj < graph[curr].size(); adj++)
		{
			if (graph[curr][adj] && !visited[adj]) {
				visited[adj] = true;
				subgraph.push_back(adj);
				dfs(adj, subgraph);
			}
		}
	}
	size_t CountVertexWithOddDegree(const vector<size_t> &subgraph)
	{
		size_t num = 0;
		for (size_t i : subgraph)
		{
			size_t degree = 0;
			for (size_t j = 0; j < graph[i].size(); j++)
			{
				if (graph[i][j]) degree++;
			}
			if (degree % 2 == 1) num++;
		}
		return num;
	}
};

int main()
{
	int cases = 0;
	size_t V, E, T;
	while (cin >> V >> E >> T) {
		if (V == 0 && E == 0 && T == 0) break;
		vector<vector<bool>> graph(V, vector<bool>(V, false));
		size_t i, j;
		for (size_t e = 0; e < E; e++)
		{
			cin >> i >> j;
			graph[i - 1][j - 1] = graph[j - 1][i - 1] = true;
		}
		Solution solution(graph, E, T);
		cout << "Case " << ++cases << ": " << solution.TotalTraverseTime() << endl;
	}
}
/*
5 3 1
1 2
1 3
4 5
4 4 1
1 2
1 4
2 3
3 4
0 0 0
*/
