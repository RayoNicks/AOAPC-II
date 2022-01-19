#include <iostream>
#include <algorithm>
#include <array>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

enum class Pixel
{
	WHITE, GRAY, BLACK
};

struct Node
{
	Pixel pixel;
	array<shared_ptr<Node>, 4> children;
	Node() : pixel(Pixel::GRAY), children({ nullptr, nullptr, nullptr, nullptr }) {}
	void SetPixel()
	{
		map<Pixel, size_t> ColorCnt;
		for (size_t i = 0; i < children.size(); i++)
		{
			ColorCnt[children[i]->pixel]++;
		}
		if (ColorCnt[Pixel::GRAY] != 0) {
			pixel = Pixel::GRAY;
		}
		else if (ColorCnt[Pixel::WHITE] == 0) {
			pixel = Pixel::BLACK;
		}
		else if (ColorCnt[Pixel::BLACK] == 0) {
			pixel = Pixel::WHITE;
		}
		else {
			pixel = Pixel::GRAY;
		}
	}
};

class Solution
{
public:
	Solution(const vector<vector<char>> &image) : image(image)
	{
		ConstructTree(root, 0, image.size(), 0, image.size());
	}
	void PrintBlackNodes(ostream &os)
	{
		traverse(&root, 1, 0);
		sort(paths.begin(), paths.end());
		if (paths.size() != 0) {
			os << paths.front();
			for (size_t i = 1; i < paths.size(); i++)
			{
				if (i % 12 == 0) {
					os << '\n';
					os << paths[i];
				}
				else os << ' ' << paths[i];
			}
			os << '\n';
		}
		os << "Total number of black nodes = " << paths.size() << '\n';
	}
	Solution(size_t length, const vector<size_t> &paths)
		: image(length, vector<char>(length, '.')), paths(paths)
	{
		for (size_t val : paths)
		{
			SetPixel(val, 0, image.size(), 0, image.size());
		}
	}
	void PrintImage(ostream &os)
	{
		for (size_t i = 0; i < image.size(); i++)
		{
			for (size_t j = 0; j < image[i].size(); j++)
			{
				cout << image[i][j];
			}
			cout << endl;
		}
	}
private:
	vector<vector<char>> image;
	vector<size_t> paths;
	Node root;
	void ConstructTree(Node &node, size_t top, size_t bottom, size_t left, size_t right)
	{
		if (left + 1 == right && top + 1 == bottom) {
			if (image[top][left] == '0') node.pixel = Pixel::WHITE;
			else node.pixel = Pixel::BLACK;
		}
		else {
			for (size_t i = 0; i < node.children.size(); i++)
			{
				node.children[i] = make_shared<Node>();
			}
			size_t VerticalMiddle = (top + bottom) / 2, HorizontalMiddle = (left + right) / 2;
			ConstructTree(*node.children[0], top, VerticalMiddle, left, HorizontalMiddle);
			ConstructTree(*node.children[1], top, VerticalMiddle, HorizontalMiddle, right);
			ConstructTree(*node.children[2], VerticalMiddle, bottom, left, HorizontalMiddle);
			ConstructTree(*node.children[3], VerticalMiddle, bottom, HorizontalMiddle, right);
			node.SetPixel();
		}
	}
	void traverse(Node* node, size_t base, size_t value)
	{
		if (node->pixel == Pixel::BLACK) {
			paths.push_back(value);
		}
		else if (node->pixel == Pixel::GRAY) {
			for (size_t i = 0; i < node->children.size(); i++)
			{
				traverse(node->children[i].get(), base * 5, value + (i + 1) * base);
			}
		}
	}
	void SetPixel(size_t val, size_t top, size_t bottom, size_t left, size_t right)
	{
		if (val == 0) {
			for (size_t i = top; i < bottom; i++)
			{
				for (size_t j = left; j < right; j++)
				{
					image[i][j] = '*';
				}
			}
		}
		else {
			size_t rem = val % 5;
			size_t VerticalMiddle = (top + bottom) / 2, HorizontalMiddle = (left + right) / 2;
			if (rem == 1) {
				SetPixel(val / 5, top, VerticalMiddle, left, HorizontalMiddle);
			}
			else if (rem == 2) {
				SetPixel(val / 5, top, VerticalMiddle, HorizontalMiddle, right);
			}
			else if (rem == 3) {
				SetPixel(val / 5, VerticalMiddle, bottom, left, HorizontalMiddle);
			}
			else if (rem == 4) {
				SetPixel(val / 5, VerticalMiddle, bottom, HorizontalMiddle, right);
			}
		}
	}
};

int main()
{
	int n = 0, ImageNo = 0;
	while (cin >> n) {
		if (n == 0) break;
		else if (n > 0) {
			vector<vector<char>> image(n, vector<char>(n, '0'));
			for (size_t i = 0; i < image.size(); i++)
			{
				for (size_t j = 0; j < image[i].size(); j++)
				{
					cin >> image[i][j];
				}
			}
			if(ImageNo != 0) cout << endl;
			Solution solution(image);
			cout << "Image " << ++ImageNo << '\n';
			solution.PrintBlackNodes(cout);
		}
		else {
			vector<size_t> paths;
			int path;
			while (cin >> path) {
				if (path == -1) break;
				paths.push_back(static_cast<size_t>(path));
			}
			if (ImageNo != 0) cout << endl;
			Solution solution(static_cast<size_t>(-n), paths);
			cout << "Image " << ++ImageNo << '\n';
			solution.PrintImage(cout);
		}
	}
	return 0;
}
/*
8
00000000
00000000
00001111
00001111
00011111
00111111
00111100
00111000
-8
9 14 17 22 23 44 63 69 88 94 113 -1
2
00
00
-4
0 -1
0
*/
