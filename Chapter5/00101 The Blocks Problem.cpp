#include <iostream>
#include <string>
#include <vector>

using namespace std;

void MoveOnto(vector<vector<int>> &blocks, vector<int> &position, int a, int b)
{
	int apos = position[a], bpos = position[b], top;
	if (a == b || apos == bpos) return;
	while (!blocks[apos].empty() && ((top = blocks[apos].back()) != a)) {
		blocks[apos].pop_back();
		blocks[top].push_back(top);
		position[top] = top;
	}
	while (!blocks[bpos].empty() && ((top = blocks[bpos].back()) != b)) {
		blocks[bpos].pop_back();
		blocks[top].push_back(top);
		position[top] = top;
	}
	blocks[bpos].push_back(a);
	blocks[apos].pop_back();
	position[a] = bpos;
}

void MoveOver(vector<vector<int>> &blocks, vector<int> &position, int a, int b)
{
	int apos = position[a], bpos = position[b], top;
	if (a == b || apos == bpos) return;
	while (!blocks[apos].empty() && ((top = blocks[apos].back()) != a)) {
		blocks[apos].pop_back();
		blocks[top].push_back(top);
		position[top] = top;
	}
	blocks[bpos].push_back(a);
	blocks[apos].pop_back();
	position[a] = bpos;
}

void PileOnto(vector<vector<int>> &blocks, vector<int> &position, int a, int b)
{
	int apos = position[a], bpos = position[b], top;
	if (a == b || apos == bpos) return;
	while (!blocks[bpos].empty() && ((top = blocks[bpos].back()) != b)) {
		blocks[bpos].pop_back();
		blocks[top].push_back(top);
		position[top] = top;
	}
	vector<int> tmp;
	while (!blocks[apos].empty() && ((top = blocks[apos].back()) != a)) {
		tmp.push_back(top);
		blocks[apos].pop_back();
	}
	tmp.push_back(a);
	blocks[apos].pop_back();
	while (!tmp.empty()) {
		blocks[bpos].push_back(tmp.back());
		position[tmp.back()] = bpos;
		tmp.pop_back();
	}
}

void PileOver(vector<vector<int>> &blocks, vector<int> &position, int a, int b)
{
	int apos = position[a], bpos = position[b], top;
	if (a == b || apos == bpos) return;
	vector<int> tmp;
	while (!blocks[apos].empty() && ((top = blocks[apos].back()) != a)) {
		tmp.push_back(top);
		blocks[apos].pop_back();
	}
	tmp.push_back(a);
	blocks[apos].pop_back();
	while (!tmp.empty()) {
		blocks[bpos].push_back(tmp.back());
		position[tmp.back()] = bpos;
		tmp.pop_back();
	}
}

int main()
{
	int n = 0;
	cin >> n;
	vector<vector<int>> blocks;
	vector<int> position;
	for (int i = 0; i < n; i++)
	{
		blocks.push_back(vector<int>());
		blocks.back().push_back(i);
		position.push_back(i);
	}
	string command, a, prep, b;
	while (cin >> command) {
		if (command == "quit") break;
		else if (command == "move") {
			cin >> a >> prep >> b;
			if (prep == "onto") {
				MoveOnto(blocks, position, stoi(a), stoi(b));
			}
			else if (prep == "over") {
				MoveOver(blocks, position, stoi(a), stoi(b));
			}
			else;
		}
		else if (command == "pile") {
			cin >> a >> prep >> b;
			if (prep == "onto") {
				PileOnto(blocks, position, stoi(a), stoi(b));
			}
			else if (prep == "over") {
				PileOver(blocks, position, stoi(a), stoi(b));
			}
			else;
		}
		else;
	}
	for (size_t i = 0; i < blocks.size(); i++)
	{
		cout << i << ":";
		for (size_t j = 0; j < blocks[i].size(); j++)
		{
			cout << ' ' << blocks[i][j];
		}
		cout << endl;
	}
	return 0;
}
/*
10
move 9 onto 1
move 8 over 1
move 7 over 1
move 6 over 1
pile 8 over 6
pile 8 over 5
move 2 over 1
move 4 over 9
quit
*/
