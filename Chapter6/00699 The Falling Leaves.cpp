#include <iostream>
#include <memory>
#include <map>
#include <vector>

using namespace std;

struct Node
{
	int value, positon;
	shared_ptr<Node> left, right;
};

class Solution
{
public:
	Solution(const vector<int> &input, size_t &index)
	{
		construct(tree, input, index, 0);
	}
	void output(ostream &os)
	{
		os << piles.begin()->second;
		for (auto iter = ++piles.begin(); iter != piles.end(); iter++)
		{
			os << ' ' << iter->second;
		}
		os << endl;
	}
private:
	Node tree;
	map<int, int> piles;
	void construct(Node &root, const vector<int> &input, size_t &index, int pos)
	{
		root.value = input.at(index++);
		root.positon = pos;
		piles[pos] += root.value;
		if (input.at(index) != -1) {
			root.left = make_shared<Node>();
			construct(*root.left, input, index, pos - 1);
		}
		else index++;
		if (input.at(index) != -1) {
			root.left = make_shared<Node>();
			construct(*root.left, input, index, pos + 1);
		}
		else index++;
	}
};

int main()
{
	int cases = 0, value;
	vector<int> input;
	while (cin >> value) {
		input.push_back(value);
	}
	size_t index = 0;
	while (input[index] != -1) {
		Solution solution(input, index);
		cout << "Case " << ++cases << ":" << endl;
		solution.output(cout);
		cout << endl;
	}
	return 0;
}
/*
5 7 -1 6 -1 -1 3 -1 -1
8 2 9 -1 -1 6 5 -1 -1 12 -1
-1 3 7 -1 -1 -1
-1
*/
