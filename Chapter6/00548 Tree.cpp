#include <iostream>
#include <algorithm>
#include <climits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
	int value;
	shared_ptr<Node> left, right;
};

class Solution
{
public:
	Solution(const vector<int> &inorder, const vector<int> &postorder)
	{
		vector<int>::const_reverse_iterator PostIter = postorder.crbegin();
		ConstructBinaryTree(tree, inorder.begin(), inorder.end(), PostIter, postorder.rend());
	}
	int GetLeafValue()
	{
		TraverseLeafNode(tree, 0);
		return LeafValue;
	}
private:
	Node tree;
	int LeastSum = INT_MAX, LeafValue;
	void ConstructBinaryTree(Node &root,
		vector<int>::const_iterator begin,
		vector<int>::const_iterator end,
		vector<int>::const_reverse_iterator &PostIter,
		vector<int>::const_reverse_iterator PostEnd)
	{
		root.value = *PostIter++;
		vector<int>::const_iterator RootIter = find(begin, end, root.value);
		if (RootIter + 1 != end) {
			root.right = make_shared<Node>();
			ConstructBinaryTree(*root.right, RootIter + 1, end, PostIter, PostEnd);
		}
		if (begin != RootIter) {
			root.left = make_shared<Node>();
			ConstructBinaryTree(*root.left, begin, RootIter, PostIter, PostEnd);
		}
	}
	void TraverseLeafNode(const Node &root, int sum)
	{
		if (root.left == nullptr && root.right == nullptr) {
			if (sum + root.value < LeastSum) {
				LeastSum = sum + root.value;
				LeafValue = root.value;
			}
			else if (sum + root.value == LeastSum) {
				LeafValue = min(LeafValue, root.value);
			}
			return;
		}
		if (root.left != nullptr) {
			TraverseLeafNode(*root.left, sum + root.value);
		}
		if (root.right != nullptr) {
			TraverseLeafNode(*root.right, sum + root.value);
		}
	}
};

vector<int> ConverseInput(const string &input)
{
	vector<int> ret;
	stringstream ss(input);
	int value;
	while (ss >> value) {
		ret.push_back(value);
	}
	return ret;
}

int main()
{
	string input;
	while (getline(cin, input)) {
		vector<int> inorder = ConverseInput(input), postorder;
		getline(cin, input);
		postorder = ConverseInput(input);
		Solution solution(inorder, postorder);
		cout << solution.GetLeafValue() << endl;
	}
	return 0;
}
/*
3 2 1 4 5 7 6
3 1 2 5 6 7 4
7 8 11 3 5 16 12 18
8 3 11 7 16 18 12 5
255
255
*/
