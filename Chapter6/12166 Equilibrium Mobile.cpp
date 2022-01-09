#include <iostream>
#include <limits>
#include <map>
#include <string>

using namespace std;

class Solution
{
public:
	Solution(const string &expr)
	{
		size_t depth = 0;
		for(size_t i = 0 ; i < expr.length(); i++)
		{
			if (expr[i] == '[') depth++;
			else if (expr[i] == ']') depth--;
			else if (expr[i] == ',') continue;
			else {
				string value;
				while (isdigit(expr[i])) {
					value.push_back(expr[i++]);
				}
				unsigned long long TotalWeight = stoull(value) * (1ULL << depth);
				freq[TotalWeight]++;
				i--;
			}
		}
	}
	int FindMinChanges()
	{
		size_t leaves = 0;
		size_t MaxFreq = numeric_limits<size_t>::min();
		for (auto iter = freq.begin(); iter != freq.end(); iter++)
		{
			leaves += iter->second;
			if (iter->second > MaxFreq) {
				MaxFreq = iter->second;
			}
		}
		return leaves - MaxFreq;
	}
private:
	map<unsigned long long, size_t> freq;
};

int main()
{
	int cases = 0;
	cin >> cases;
	cin.get();
	for (int c = 0; c < cases; c++)
	{
		string expr;
		cin >> expr;
		Solution soluton(expr);
		cout << soluton.FindMinChanges() << endl;
	}
	return 0;
}
/*
3
[[3,7],6]
40
[[2,3],[4,5]]
*/
