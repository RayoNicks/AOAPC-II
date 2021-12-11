#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX_RETRY 7

bool update(const string &strPuzzle, vector<bool> &vbSolved, char chGuess)
{
	bool bCorrect = false;
	for (size_t j = 0; j < strPuzzle.size(); j++)
	{
		if (chGuess == strPuzzle[j]){
			vbSolved[j] = true;
			bCorrect = true;
		}
	}
	return bCorrect;
}

bool check(const vector<bool> &vbSolved)
{
	for (size_t k = 0; k < vbSolved.size(); k++)
	{
		if (!vbSolved[k]) return false;
	}
	return true;
}

void game(const int round, const string &strPuzzle, const string &strGuess)
{
	cout << "Round " << round << endl;
	vector<bool> vbSolved(strPuzzle.size(), false);
	vector<bool> vbGuessed(26, false);
	int time = MAX_RETRY;
	for (size_t i = 0; i < strGuess.size(); i++)
	{
		if (vbGuessed[strGuess[i] - 'a']) continue;
		vbGuessed[strGuess[i] - 'a'] = true;
		if (update(strPuzzle, vbSolved, strGuess[i])){
			if (check(vbSolved)){
				cout << "You win." << endl;
				return;
			}
		}
		else{
			time--;
			if (time == 0){
				cout << "You lose." << endl;
				return;
			}
		}
	}
	cout << "You chickened out." << endl;
	return;
}

int main()
{
	int round = 0;
	string strPuzzle, strGuess;
	while (cin >> round){
		if (round == -1) break;
		cin.get();
		cin >> strPuzzle >> strGuess;
		game(round, strPuzzle, strGuess);
	}
	return 0;
}
/*
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
*/
