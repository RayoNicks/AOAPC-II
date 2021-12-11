#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Matrix
{
	char name;
	int row, column;
};

istream& operator >> (istream &is, Matrix &m)
{
	is >> m.name >> m.row >> m.column;
	return is;
}

class Solution
{
public:
	Solution(int n, istream &is)
	{
		for (int i = 0; i < n; i++)
		{
			Matrix matrix;
			is >> matrix;
			matrixs[matrix.name] = matrix;
		}
	};
	bool CheckValidation(const string &expr)
	{
		int column = 0;
		for (char ch : expr)
		{
			if (isupper(ch)) {
				if (column == 0) column = matrixs[ch].column;
				else if (column != matrixs[ch].row) return false;
				else column = matrixs[ch].column;
			}
		}
		return true;
	}
	void ComputeMultiplications(const string &expr, int &multiplication, int &row, int &column)
	{
		if (expr.length() == 0) {
			multiplication = 0, row = 0, column = 0;
			return;
		}
		if (expr.length() == 1) {
			Matrix &matrix = matrixs[expr[0]];
			multiplication = 0, row = matrix.row, column = matrix.column;
			return;
		}
		int mul[2], r[2], c[2];
		if (expr[0] == '(') {
			size_t RightIndex = FindRightParentheses(expr, 0);
			ComputeMultiplications(expr.substr(1, RightIndex - 1), mul[0], r[0], c[0]);
			ComputeMultiplications(expr.substr(RightIndex + 1), mul[1], r[1], c[1]);
		}
		else {
			ComputeMultiplications(string(1, expr[0]), mul[0], r[0], c[0]);
			ComputeMultiplications(expr.substr(1), mul[1], r[1], c[1]);
		}
		if (r[1] == 0 && c[1] == 0) {
			multiplication = mul[0] + mul[1];
			row = r[0], column = c[0];
		}
		else {
			multiplication = mul[0] + mul[1] + r[0] * c[0] * c[1];
			row = r[0], column = c[1];
		}
		return;
	}
private:
	map<char, Matrix> matrixs;
	size_t FindRightParentheses(const string &expr, size_t LeftIndex)
	{
		int count = 1;
		for (size_t i = LeftIndex + 1; i < expr.length(); i++)
		{
			if (expr.at(i) == '(') count++;
			else if (expr.at(i) == ')') count--;
			else;
			if (count == 0) return i;
		}
		return expr.length();
	}
};

int main()
{
	int n = 0;
	cin >> n;
	Solution solution(n, cin);
	string expr;
	while (cin >> expr) {
		if (!solution.CheckValidation(expr)) cout << "error" << endl;
		else {
			int mul, row, column;
			solution.ComputeMultiplications(expr, mul, row, column);
			cout << mul << endl;
		}
	}
	return 0;
}
/*
9
A 50 10
B 10 20
C 20 5
D 30 35
E 35 15
F 15 5
G 5 10
H 10 20
I 20 25
A
B
C
(AA)
(AB)
(AC)
(A(BC))
((AB)C)
(((((DE)F)G)H)I)
(D(E(F(G(HI)))))
((D(EF))((GH)I))
*/
