#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <vector>

#define BASE 1000000000000000000

using namespace std;

struct TrieNode
{
	int index;
	array<TrieNode*, 10> next;

	TrieNode() : index(-1)
	{
		next.fill(nullptr);
	}

	void add(const string &s, int value)
	{
		TrieNode* ptr = this;
		for (char c : s)
		{
			if (ptr->next[c - '0'] == nullptr) {
				ptr->next[c - '0'] = new TrieNode();
			}
			ptr = ptr->next[c - '0'];
			if (ptr->index == -1) {
				ptr->index = value;
			}
			else {
				ptr->index = min(ptr->index, value);
			}
		}
	}

	int search(const string &prefix)
	{
		TrieNode* ptr = this;
		for (char c : prefix)
		{
			if (ptr->next[c - '0'] == nullptr) {
				return -1;
			}
			ptr = ptr->next[c - '0'];
		}
		return ptr->index;
	}
};

string Convert2String(const vector<long long> &fib)
{
	string s, tmp;
	s.append(to_string(fib.back()));
	for (auto riter = fib.rbegin() + 1; riter != fib.rend(); riter++)
	{
		tmp = to_string(*riter);
		s.append(18 - tmp.length(), '0');
		s.append(tmp);
	}
	return s;
}

vector<long long> PrecomputeFib(const vector<long long> &fn_2, vector<long long> &fn_1)
{
	long long carry = 0;
	size_t i = 0, j = 0;
	vector<long long> result;
	while (i < fn_2.size() && j < fn_1.size()) {
		result.push_back(fn_2[i] + fn_1[j] + carry);
		carry = result.back() / BASE;
		result.back() %= BASE;
		i++, j++;
	}
	while (j < fn_1.size()) {
		result.push_back(fn_1[j] + carry);
		carry = result.back() / BASE;
		result.back() %= BASE;
		j++;
	}
	if (carry != 0) {
		result.push_back(carry);
	}
	if (result.size() > 4) {
		fn_1.assign(fn_1.begin() + (result.size() - 4), fn_1.end());
		result.assign(result.begin() + result.size() - 4, result.end());
	}
	return result;
}

void PrecomputeFibPrefix(TrieNode &root)
{
	vector<long long> fn_2(1, 1), fn_1(1, 1), fn;
	int index = 2;
	root.add("1", 0);
	while (index < 100000) {
		fn = PrecomputeFib(fn_2, fn_1);
		root.add(Convert2String(fn), index);
		fn_2 = fn_1;
		fn_1 = fn;
		index++;
	}
}

int main()
{
	int n = 0;
	cin >> n;
	TrieNode root;
	PrecomputeFibPrefix(root);
	for (int i = 0; i < n; i++)
	{
		string prefix;
		cin >> prefix;
		cout << "Case #" << i + 1 << ": " << root.search(prefix) << endl;
	}
	return 0;
}
/*
15
1
12
123
1234
12345
9
98
987
9876
98765
89
32
51075176167176176176
347746739
5610
*/
