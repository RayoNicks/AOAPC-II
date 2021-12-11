#include <iostream>
#include <algorithm>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
	int value;
	string path;
	Node(const string &pair)
	{
		string::size_type pos = pair.find(',');
		value = stoi(pair.substr(1, pos - 1));
		path.assign(pair.substr(pos + 1, pair.length() - pos - 2));
	}
};

bool CheckCompleteness(vector<Node> &nodes)
{
	if (!nodes.front().path.empty()) {
		return false;
	}
	for (size_t i = 1; i < nodes.size(); i++)
	{
		if (nodes[i - 1].path == nodes[i].path) {
			return false;
		}
	}
	set<string> paths;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		const string &path = nodes[i].path;
		for (size_t len = 1; len < path.length() - 1; len++)
		{
			if (paths.find(path.substr(0, len)) == paths.end()) {
				return false;
			}
		}
		paths.insert(path);
	}
	return true;
}

void traverse(const vector<Node> &nodes)
{
	cout << nodes.front().value;
	for (size_t i = 1; i < nodes.size(); i++)
	{
		cout << ' ' << nodes[i].value;
	}
	cout << endl;
}

int main()
{
	vector<Node> nodes;
	string line;
	while (cin >> line) {
		stringstream ss(line);
		string pairs;
		while (ss >> pairs) {
			if (pairs == "()") {
				sort(nodes.begin(), nodes.end(), [](const Node &n1, const Node &n2)
				{
					if (n1.path.length() == n2.path.length())
						return n1.path < n2.path;
					else
						return n1.path.length() < n2.path.length();
				});
				if (CheckCompleteness(nodes)) {
					traverse(nodes);
				}
				else {
					cout << "not complete" << endl;
				}
				nodes.clear();
			}
			else {
				nodes.emplace_back(pairs);
			}
		}
	}
	return 0;
}
/*
(11,LL) (7,LLL) (8,R)
(5,) (4,L) (13,RL) (2,LLR) (1,RRR) (4,RR) ()
(3,L) (4,R) ()
*/
