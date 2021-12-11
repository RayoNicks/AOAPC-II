#include <iostream>
#include <array>
#include <bitset>
#include <climits>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Vertex
{
	size_t no;
	size_t Indegree, Outdegree;
	Vertex() : no(0), Indegree(0), Outdegree(0) {}
};

class Solution
{
public:
	Solution(const vector<string> &plates)
		: TotalEdges(plates.size()), TotalVertex(0),
		EulerPathStart(UINT_MAX), EulerPathEnd(UINT_MAX)
	{
		graph.fill(array<size_t, 26>());
		for (const string &plate : plates)
		{
			size_t front = plate.front() - 'a', back = plate.back() - 'a';
			vertexes[front].no = front;
			vertexes[back].no = back;
			if (front == back) {
				TotalEdges--;
				continue;
			}
			graph[front][back]++;
			vertexes[front].Outdegree++;
			vertexes[back].Indegree++;
		}
		TotalVertex = vertexes.size();
	}
	bool solve()
	{
		if (!CheckDegree()) return false;
		if (!CheckConnectivity()) return false;
		found = false;
		ArrangePlate(EulerPathStart, TotalEdges);
		return found;
	}
private:
	array<array<size_t, 26>, 26> graph;
	map<size_t, Vertex> vertexes;
	size_t TotalEdges, TotalVertex;
	size_t EulerPathStart, EulerPathEnd;
	bool found;
	bool CheckDegree()
	{
		for (const pair<size_t, Vertex> &p : vertexes)
		{
			const Vertex &vertex = p.second;
			if (vertex.Indegree == vertex.Outdegree) continue;
			else if (vertex.Indegree + 1 == vertex.Outdegree) {
				if (EulerPathStart == UINT_MAX) {
					EulerPathStart = p.first;
				}
				else return false;
			}
			else if (vertex.Indegree == vertex.Outdegree + 1) {
				if (EulerPathEnd == UINT_MAX) {
					EulerPathEnd = p.first;
				}
				else return false;
			}
			else return false;
		}
		if (EulerPathStart == UINT_MAX && EulerPathEnd == UINT_MAX) {
			EulerPathStart = EulerPathEnd = vertexes.begin()->first;
		}
		return EulerPathStart != UINT_MAX && EulerPathEnd != UINT_MAX;
	}
	bool CheckConnectivity()
	{
		queue<size_t> q;
		bitset<26> visited(string(26, '0'));
		size_t remain = TotalVertex - 1;
		visited.set(EulerPathStart);
		q.push(EulerPathStart);
		while (remain != 0 && !q.empty()) {
			const array<size_t, 26> &adjacents = graph[q.front()];
			for(size_t j = 0; j < adjacents.size(); j++)
			{
				if (adjacents[j] != 0 && !visited.test(j)) {
					remain--;
					visited.set(j);
					q.push(j);
				}
			}
			q.pop();
		}
		return remain == 0;
	}
	void ArrangePlate(size_t curr, size_t LeftEdge)
	{
		if (LeftEdge == 0) {
			found = true;
			return;
		}
		array<size_t, 26> &adjacents = graph[curr];
		for (size_t j = 0; j < adjacents.size(); j++)
		{
			if (!found && adjacents[j] > 0) {
				adjacents[j]--;
				ArrangePlate(j, LeftEdge - 1);
				adjacents[j]++;
			}
		}
	}
};

int main()
{
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
	{
		int N;
		cin >> N;
		vector<string> plates;
		for (int j = 0; j < N; j++)
		{
			string plate;
			cin >> plate;
			plates.push_back(plate);
		}
		Solution solution(plates);
		if (solution.solve()) {
			cout << "Ordering is possible." << endl;
		}
		else {
			cout << "The door cannot be opened." << endl;
		}
	}
	return 0;
}
/*
3
2
acm
ibm
3
acm
malform
mouse
2
ok
ok
*/
