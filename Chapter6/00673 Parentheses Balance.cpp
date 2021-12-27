#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
	Solution(const string &expr) : expr(expr) {}
	bool correctness()
	{
		vector<char> stack;
		for (size_t i = 0; i < expr.size(); i++)
		{
			if (expr[i] == '(' || expr[i] == '[') {
				stack.push_back(expr[i]);
			}
			else if (expr[i] == ')') {
				if (stack.empty() || stack.back() != '(') return false;
				else stack.pop_back();
			}
			else if (expr[i] == ']') {
				if (stack.empty() || stack.back() != '[') return false;
				else stack.pop_back();
			}
		}
		return stack.empty();
	}
private:
	string expr;
};

int main()
{
	size_t n = 0;
	cin >> n;
	cin.get();
	for (size_t i = 0; i < n; i++)
	{
		string expr;
		getline(cin, expr);
		Solution solution(expr);
		if (solution.correctness()) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}
	return 0;
}
/*
3
([])
(([()])))
([()[]()])()
*/
