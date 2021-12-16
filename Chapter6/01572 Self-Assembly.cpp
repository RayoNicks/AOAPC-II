#include <iostream>
#include <array>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
	Solution(const vector<string> &molecules)
		: graph(52, vector<bool>(52, false)), visited(52, false), circle(false)
	{
		for (const string &molecule : molecules)
		{
			array<char, 4> labels;
			for (size_t i = 0; i < molecule.length(); i += 2)
			{
				if (molecule[i] == '0' && molecule[i + 1] == '0') {
					labels[i >> 1] = '0';
				}
				else if (molecule[i + 1] == '+') {
					labels[i >> 1] = toupper(molecule[i]);
				}
				else {
					labels[i >> 1] = tolower(molecule[i]);
				}
			}
			for (size_t i = 0; i < labels.size(); i++)
			{
				if (labels[i] == '0') continue;
				char adj = GetConnected(labels.at(i));
				for (size_t j = 0; j < labels.size(); j++)
				{
					if (i == j || labels[j] == '0') continue;
					graph[Char2Index(adj)][Char2Index(labels.at(j))] = true;
				}
			}
		}
		for (size_t i = 0; i < graph.size(); i++)
		{
			visited[i] = true;
			SearchCircle(i);
			visited[i] = false;
			if (circle) break;
		}
	}
	bool HasCircle()
	{
		return circle;
	}
private:
	vector<vector<bool>> graph;
	vector<bool> visited;
	bool circle;
	int Char2Index(char ch)
	{
		if (isupper(ch)) return ch - 'A';
		else return ch - 'a' + 26;
	}
	char GetConnected(char ch)
	{
		if (isupper(ch)) return tolower(ch);
		else return toupper(ch);
	}
	void SearchCircle(size_t current)
	{
		for (size_t i = 0; i < graph[current].size(); i++)
		{
			if (!graph[current][i]) continue;
			if (visited[i]) {
				circle = true;
			}
			else {
				visited[i] = true;
				SearchCircle(i);
				visited[i] = false;
			}
			if (circle) break;
		}
	}
};

int main()
{
	size_t n = 0;
	while (cin >> n) {
		string molecule;
		vector<string> molecules;
		for (size_t i = 0; i < n; i++)
		{
			cin >> molecule;
			molecules.push_back(molecule);
		}
		Solution solution(molecules);
		if (solution.HasCircle()) {
			cout << "unbounded" << endl;
		}
		else {
			cout << "bounded" << endl;
		}
	}
	return 0;
}
/*
3
A+00A+A+ 00B+D+A- B-C+00C+
1
K+K-Q+Q-
*/
