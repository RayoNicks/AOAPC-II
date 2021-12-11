#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

void findPalindrome(const string &str, vector<vector<bool>> &Palindrome)
{
	Palindrome[0][0] = true;
	for (size_t end = 1; end < str.size(); end++)
	{
		Palindrome[end][end] = true;
		Palindrome[end - 1][end] = Palindrome[end][end - 1] = str[end - 1] == str[end];
		for (size_t begin = 1; begin < end; begin++)
		{
			if (Palindrome[begin][end - 1] && str[begin - 1] == str[end]) {
				Palindrome[begin - 1][end] = true;
				Palindrome[end][begin - 1] = true;
			}
		}
	}
}

void findMinGroup(const string &str, const vector<vector<bool>> &Palindrome)
{
	vector<int> Group(str.size(), INT_MAX);
	Group[0] = 1;
	for (size_t end = 1; end < str.size(); end++)
	{
		if (Palindrome[0][end]) Group[end] = 1;
		for (size_t begin = 1; begin <= end; begin++)
		{
			if (Palindrome[begin][end]) {
				if (Group[end] > Group[begin - 1] + 1) {
					Group[end] = Group[begin - 1] + 1;
				}
			}
		}
	}
	cout << Group.back() << endl;
}

int main()
{
	int n = 0;
	string str;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> str;
		vector<vector<bool>> Palindrome(str.size(), vector<bool>(str.size(), false));
		findPalindrome(str, Palindrome);
		findMinGroup(str, Palindrome);
	}
	return 0;
}
/*
3
racecar
fastcar
aaadbccb
*/
