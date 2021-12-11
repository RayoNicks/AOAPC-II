#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Player
{
	string name;
	size_t position = 0;
	bool amateur = false, rank = false, HasPrize = false, tie = false;
	vector<int> scores;
	int total;
	double prize = 0.0;
};

istream &operator>>(istream &is, Player &player)
{
	string line, score;
	getline(is, line);
	player.name.assign(line.substr(0, 20));
	while (!player.name.empty() && player.name.back() == ' ') {
		player.name.pop_back();
	}
	player.amateur = player.name.back() == '*';
	istringstream iss(line.substr(20));
	while (iss >> score) {
		if (score != "DQ") {
			player.scores.push_back(stoi(score));
		}
	}
	return is;
}

ostream &operator<<(ostream &os, const Player &player)
{
	os << left;
	os << setw(20) << player.name << ' ';
	if (player.tie) {
		os << setw(9) << to_string(player.position) + 'T' << ' ';
	}
	else if (!player.rank) {
		os << string(10, ' ');
	}
	else {
		os << setw(9) << to_string(player.position) << ' ';
	}
	for (size_t i = 0; i < 4; i++)
	{
		if (i >= player.scores.size()) {
			os << string(5, ' ');
		}
		else {
			os << setw(4) << player.scores[i] << ' ';
		}
	}
	if (player.scores.size() != 4) {
		os << "DQ";
	}
	else if (player.amateur || !player.HasPrize) {
		os << player.total;
	}
	else {
		os << setw(9) << player.total << ' ';
		os << '$';
		os << right << fixed << setw(9) << setfill(' ') << setprecision(2) << player.prize;
	}
	return os;
}

void CutPlayer(vector<Player> &players, size_t &CutNum, size_t &RankNum)
{
	size_t round = 2;
	auto DisqualifyPred = [&round](const Player &player)->bool
	{
		return player.scores.size() >= round;
	};
	auto AggregateScorePred = [&round](Player &player)->void
	{
		player.total = 0;
		for (size_t i = 0; i < round && i < player.scores.size(); i++)
		{
			player.total += player.scores[i];
		}
	};
	auto SameRoundPartitionPred = [](const Player &p1, const Player &p2)->bool
	{
		if (p1.total != p2.total) return p1.total < p2.total;
		else return p1.name < p2.name;
	};
	auto DiffRoundPartitionPred = [](const Player &p1, const Player &p2)->bool
	{
		if (p1.scores.size() != p2.scores.size()) return p1.scores.size() > p2.scores.size();
		else if (p1.total != p2.total) return p1.total < p2.total;
		else return p1.name < p2.name;
	};
	auto CutIter = stable_partition(players.begin(), players.end(), DisqualifyPred);
	for_each(players.begin(), CutIter, AggregateScorePred);
	sort(players.begin(), CutIter, SameRoundPartitionPred);
	if (CutIter - players.begin() > 70) {
		int TieScore = (players.begin() + 69)->total;
		for (auto iter = players.begin() + 70; iter != CutIter; iter++)
		{
			if (iter->total != TieScore) {
				CutIter = iter;
				break;
			}
		}
	}
	CutNum = CutIter - players.begin();

	round = 4;
	auto DisqualifiedIter = stable_partition(players.begin(), CutIter, DisqualifyPred);
	for_each(players.begin(), DisqualifiedIter, AggregateScorePred);
	sort(players.begin(), DisqualifiedIter, SameRoundPartitionPred);
	for_each(DisqualifiedIter, CutIter, AggregateScorePred);
	sort(DisqualifiedIter, CutIter, DiffRoundPartitionPred);
	RankNum = DisqualifiedIter - players.begin();
}

void ProcessTiePlayer(vector<Player> &players, vector<double> percents,
	size_t TieIndex, size_t TieNum, size_t AmateurNum, size_t PercentIndex, size_t position, double purse)
{
	double PercentSum = 0.0, percent;
	size_t PercentNum = TieNum - AmateurNum;
	for (size_t j = 0; j < PercentNum && PercentIndex + j < percents.size(); j++)
	{
		PercentSum += percents[PercentIndex + j];
	}
	percent = PercentSum / (TieNum - AmateurNum);
	for (size_t j = TieIndex; j < TieIndex + TieNum; j++)
	{
		players[j].rank = true;
		players[j].position = position;
		players[j].HasPrize = !players[j].amateur && PercentIndex < percents.size();
		players[j].tie = players[j].HasPrize && (TieNum - AmateurNum) > 1;
		if (players[j].HasPrize) {
			players[j].prize = purse * percent / 100.0;
		}
	}
}

void AllocatePrize(vector<Player> &players, const vector<double> &percents, double purse, size_t RankNum)
{
	int TieScore = players[0].total, position = 1;
	size_t TieIndex = 0, PercentIndex = 0;
	size_t TieNum = 1, AmateurNum = players[0].amateur ? 1 : 0;
	for (size_t i = 1; i < RankNum; i++)
	{
		if (players[i].total == TieScore) {
			TieNum++;
			if (players[i].amateur) {
				AmateurNum++;
			}
		}
		else {
			ProcessTiePlayer(players, percents, TieIndex, TieNum, AmateurNum, PercentIndex, position, purse);
			TieScore = players[i].total, position += TieNum;
			TieIndex = i, PercentIndex += TieNum - AmateurNum;
			TieNum = 1, AmateurNum = players[i].amateur ? 1 : 0;
		}
	}
	ProcessTiePlayer(players, percents, TieIndex, TieNum, AmateurNum, PercentIndex, position, purse);
}

void PrintResult(vector<Player> &players, size_t CutNum)
{
	cout << "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	for (size_t i = 0; i < CutNum; i++)
	{
		cout << players[i] << endl;
	}
}

int main()
{
	int cases = 0;
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		double purse = 0.0;
		cin >> purse;
		vector<double> percents(70, 0.0);
		for (size_t i = 0; i < 70; i++)
		{
			cin >> percents[i];
		}
		size_t PlayerNum;
		cin >> PlayerNum;
		cin.get();
		vector<Player> players(PlayerNum);
		for (size_t i = 0; i < PlayerNum; i++)
		{
			cin >> players[i];
		}
		size_t CutNum, RankNum;
		CutPlayer(players, CutNum, RankNum);
		AllocatePrize(players, percents, purse, RankNum);
		PrintResult(players, CutNum);
		if (i != cases - 1) {
			cout << endl;
		}
	}
	return 0;
}
/*

*/
