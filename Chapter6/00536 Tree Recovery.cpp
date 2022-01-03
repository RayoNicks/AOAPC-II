#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
	Solution(const string &preorder, const string &inorder)
		: preorder(preorder), inorder(inorder)
	{
		size_t curr = 0;
		size_t root = inorder.find(preorder[curr++]);
		RecoverPostorder(0, root, curr);
		RecoverPostorder(root + 1, inorder.length(), curr);
		postorder.push_back(inorder[root]);
	}
	string result()
	{
		return postorder;
	}
private:
	string preorder, inorder, postorder;
	void RecoverPostorder(size_t start, size_t end, size_t &curr)
	{
		if (start == end) return;
		size_t root = inorder.find(preorder[curr++]);
		RecoverPostorder(start, root, curr);
		RecoverPostorder(root + 1, end, curr);
		postorder.push_back(inorder[root]);
	}
};

int main()
{
	string preorder, inorder;
	while (cin >> preorder >> inorder) {
		Solution solution(preorder, inorder);
		cout << solution.result() << endl;
	}
	return 0;
}
/*
DBACEGF ABCDEFG
BCAD CBAD
*/
