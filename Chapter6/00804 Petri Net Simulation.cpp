#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Transition
{
	map<size_t, size_t> input, output;
	bool fire(vector<size_t> &tokens) const
	{
		for (auto iter = input.begin(); iter != input.end(); iter++)
		{
			if (tokens[iter->first] < iter->second) return false;
		}
		for (auto iter = input.begin(); iter != input.end(); iter++)
		{
			tokens[iter->first] -= iter->second;
		}
		for (auto iter = output.begin(); iter != output.end(); iter++)
		{
			tokens[iter->first] += iter->second;
		}
		return true;
	}
};

class Solution
{
public:
	Solution(const vector<size_t> &tokens, const vector<Transition> &transitions, int nf)
		: transitions(transitions), LeftTokens(tokens), dead(false), FireCounter(0), nf(nf)
	{
		simulation(tokens, 0);
	}
	string result(int cases)
	{
		ostringstream oss;
		oss << "Case " << cases << ": ";
		if (dead) oss << "dead after " << FireCounter;
		else oss << "still live after " << nf;
		oss << " transitions\n";
		oss << "Places with tokens:";
		for (size_t i = 0; i < LeftTokens.size(); i++)
		{
			if (LeftTokens[i] > 0) {
				oss << ' ' << i + 1 << " (" << LeftTokens[i] << ')';
			}
		}
		oss << endl;
		return oss.str();
	}
private:
	vector<Transition> transitions;
	vector<size_t> LeftTokens;
	bool dead;
	int FireCounter, nf;
	void simulation(const vector<size_t> &tokens, int step)
	{
		for (int step = 0; step < nf; step++)
		{
			bool fired = false;
			for (const Transition &transition : transitions)
			{
				if (transition.fire(LeftTokens)) {
					fired = true;
					break;
				}
			}
			if (!fired) {
				FireCounter = step;
				dead = true;
				break;
			}
		}
	}
};

int main()
{
	int cases = 0, np, nt, nf;
	while (cin >> np) {
		if (np == 0) break;
		cases++;
		vector<size_t> tokens;
		size_t token;
		for (int i = 0; i < np; i++)
		{
			cin >> token;
			tokens.push_back(token);
		}
		cin >> nt;
		vector<Transition> transitons;
		for (int i = 0; i < nt; i++)
		{
			transitons.push_back(Transition());
			int place;
			while (cin >> place) {
				if (place < 0) {
					transitons.back().input[static_cast<size_t>(-(place + 1))]++;
				}
				else if (place > 0) {
					transitons.back().output[static_cast<size_t>(place - 1)]++;
				}
				else break;
			}
		}
		cin >> nf;
		Solution solution(tokens, transitons, nf);
		cout << solution.result(cases) << endl;
	}
	return 0;
}
/*
2
1 0
2
-1 2 0
-2 1 0
100
3
3 0 0
3
-1 2 0
-2 -2 3 0
-3 1 0
100
0
*/
