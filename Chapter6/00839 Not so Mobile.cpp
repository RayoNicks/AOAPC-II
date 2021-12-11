#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Lever
{
	int W_l, D_l, W_r, D_r;
};

struct Node
{
	int weight, D_l, D_r;
	shared_ptr<Node> left, right;
};

class Solution
{
public:
	Solution(istream &is)
	{
		string line;
		while (getline(is, line)) {
			if (line.empty()) break;
			levers.push_back(Lever());
			stringstream ss(line);
			ss >> levers.back().W_l >> levers.back().D_l >> levers.back().W_r >> levers.back().D_r;
		}
		size_t index = 0;
		construct(tree, index);
	}
	bool equilibrium = true;
private:
	vector<Lever> levers;
	Node tree;
	void construct(Node &root, size_t &index)
	{
		const Lever &lever = levers.at(index++);
		root.D_l = lever.D_l, root.D_r = lever.D_r;
		if (lever.W_l == 0 && lever.W_r == 0) {
			root.left = make_shared<Node>();
			construct(*root.left, index);
			root.right = make_shared<Node>();
			construct(*root.right, index);
			root.weight = root.left->weight + root.right->weight;
			equilibrium &= root.left->weight * lever.D_l == root.right->weight * lever.D_r;
		}
		else if (lever.W_l != 0 && lever.W_r != 0) {
			root.weight = lever.W_l + lever.W_r;
			equilibrium &= lever.W_l * lever.D_l == lever.W_r * lever.D_r;
		}
		else if (lever.W_l != 0) {
			root.right = make_shared<Node>();
			construct(*root.right, index);
			root.weight = root.right->weight + lever.W_l;
			equilibrium &= lever.W_l * lever.D_l == root.right->weight * lever.D_r;
		}
		else {
			root.left = make_shared<Node>();
			construct(*root.left, index);
			root.weight = root.left->weight + lever.W_r;
			equilibrium &= root.left->weight * lever.D_l == lever.W_r * lever.D_r;
		}
	}
};

int main()
{
	int cases;
	cin >> cases;
	cin.get();
	cin.get();
	for (int c = 0; c < cases; c++)
	{
		if (c != 0) cout << endl;
		Solution solution(cin);
		if (solution.equilibrium) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
/*
1

0 2 0 4
0 3 0 1
1 1 1 1
2 4 4 2
1 6 3 2
*/
