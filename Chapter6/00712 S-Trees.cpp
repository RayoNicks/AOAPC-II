#include <iostream>
#include <string>
#include <vector>

using namespace std;

char EvaluateSTree(const vector<size_t> &indices, const string &terminal, const string &vva)
{
	size_t n = 0;
	for (auto index : indices)
	{
		if (vva[index - 1] == '1') {
			n = 2 * n + 2;
		}
		else {
			n = 2 * n + 1;
		}
	}
	n -= (1 << indices.size()) - 1;
	return terminal[n];
}

int main()
{
	size_t cases = 0, n;
	while (cin >> n) {
		if (n == 0) break;
		cin.get();
		string variable;
		vector<size_t> indices;
		for (size_t i = 0; i < n; i++)
		{
			cin >> variable;
			indices.push_back(stoul(variable.substr(1)));
		}
		string terminal, vva;
		size_t m;
		cin >> terminal;
		cin >> m;
		cout << "S-Tree #" << ++cases << ":\n";
		for (size_t i = 0; i < m; i++)
		{
			cin >> vva;
			cout << EvaluateSTree(indices, terminal, vva);
		}
		cout << '\n' << endl;
	}
	return 0;
}
/*
3
x1 x2 x3
00000111
4
000
010
111
110
3
x3 x1 x2
00010011
4
000
010
111
110
0
*/
