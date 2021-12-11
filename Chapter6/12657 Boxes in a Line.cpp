#include <iostream>
#include <vector>

using namespace std;

struct Box
{
	int no;
	int left, right;
	Box(int n, int l, int r) : no(n), left(l), right(r) {};
};

struct Boxes
{
	vector<Box> boxes;
	Boxes(int n)
	{
		boxes.emplace_back(0, 0, 1);
		for (int i = 1; i <= n; i++)
		{
			boxes.emplace_back(i, i - 1, i + 1);
		}
		boxes.emplace_back(0, n, 0);
	}
	void remove(int X)
	{
		Box &x = boxes[X];
		boxes[x.left].right = x.right;
		boxes[x.right].left = x.left;
	}
	void InsertLeft(int X, int Y)
	{
		Box &y = boxes[Y];
		boxes[X].right = Y;
		boxes[X].left = y.left;
		boxes[y.left].right = X;
		y.left = X;
	}
	void InsertRight(int X, int Y)
	{
		Box &y = boxes[Y];
		boxes[X].left = Y;
		boxes[X].right = y.right;
		boxes[y.right].left = X;
		y.right = X;
	}
	void swap(int X, int Y)
	{
		if (boxes[Y].right == X) return swap(Y, X);
		int XRight = boxes[X].right;
		remove(X);
		InsertRight(X, Y);
		if (XRight != Y) {
			remove(Y);
			InsertLeft(Y, XRight);
		}
	}
	unsigned int GetOddSum(bool reverse)
	{
		unsigned int sum = 0;
		size_t count = (boxes.size() - 2) / 2 + boxes.size() % 2;
		if (reverse) {
			int no = boxes.back().left;
			for (size_t i = 0; i < count; i++)
			{
				sum += no;
				no = boxes[no].left;
				no = boxes[no].left;
			}
		}
		else {
			int no = boxes.front().right;
			for (size_t i = 0; i < count; i++)
			{
				sum += no;
				no = boxes[no].right;
				no = boxes[no].right;
			}
		}
		return sum;
	}
};

int main()
{
	int cases = 1;
	int n, m;
	while (cin >> n) {
		Boxes boxes(n);
		cin >> m;
		bool reverse = false;
		int cmd, X, Y;
		for (int i = 0; i < m; i++)
		{
			cin >> cmd;
			switch (cmd)
			{
			case 1:
				cin >> X >> Y;
				boxes.remove(X);
				if (reverse) boxes.InsertRight(X, Y);
				else boxes.InsertLeft(X, Y);
				break;
			case 2:
				cin >> X >> Y;
				boxes.remove(X);
				if (reverse) boxes.InsertLeft(X, Y);
				else boxes.InsertRight(X, Y);
				break;
			case 3:
				cin >> X >> Y;
				boxes.swap(X, Y);
				break;
			case 4:
				reverse = reverse == false;
				break;
			}
		}
		cout << "Case " << cases++ << ": " << boxes.GetOddSum(reverse) << endl;
	}
	return 0;
}
/*
6 4
1 1 4
2 3 5
3 1 6
4
6 3
1 1 4
2 3 5
3 1 6
100000 1
4
*/
