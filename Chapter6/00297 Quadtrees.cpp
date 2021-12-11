#include <iostream>
#include <array>
#include <memory>
#include <string>

using namespace std;

struct Node
{
	char color;
	int depth, black;
	array<shared_ptr<Node>, 4> children;
};

class Solution
{
public:
	Solution(const string &image1, const string &image2)
	{
		size_t index1 = 0, index2 = 0;
		construct(tree1, image1, index1, 0);
		construct(tree2, image2, index2, 0);
		AddImage(tree1, tree2);
	}
	int black = 0;
private:
	Node tree1, tree2;
	void construct(Node &root, const string &image, size_t &index, int depth)
	{
		root.color = image.at(index++);
		root.depth = depth;
		if (root.color == 'p') {
			for (size_t i = 0; i < root.children.size(); i++)
			{
				root.children[i] = make_shared<Node>();
				construct(*root.children[i], image, index, depth + 1);
				root.black += root.children[i]->black;
			}
		}
		else {
			int len = 1 << (5 - root.depth);
			root.black = root.color == 'f' ? len * len : 0;
		}
	}
	void AddImage(const Node &root1, const Node &root2)
	{
		int len = 1 << (5 - root1.depth);
		if (root1.color == 'f' || root2.color == 'f') {
			black += len * len;
		}
		else if (root1.color == 'e') {
			black += root2.black;
		}
		else if (root2.color == 'e') {
			black += root1.black;
		}
		else {
			for (size_t i = 0; i < root1.children.size(); i++)
			{
				AddImage(*root1.children[i], *root2.children[i]);
			}
		}
	}
};

int main()
{
	int N = 0;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		string image1, image2;
		cin >> image1 >> image2;
		Solution solution(image1, image2);
		cout << "There are " << solution.black << " black pixels." << endl;
	}
	return 0;
}
/*
3
ppeeefpffeefe
pefepeefe
peeef
peefe
peeef
peepefefe
*/
