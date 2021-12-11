#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <climits>

#define LEFT 0
#define RIGHT 1

using namespace std;

void buildTimeTable(
	map<int, vector<array<bool, 2>>> &mTimeTable,
	const vector<int> &viTravel,
	const vector<int> &viLeft,
	const vector<int> &viRight)
{
	size_t stations = viTravel.size() + 1;

	for (auto ldepart : viLeft)
	{
		if (mTimeTable.find(ldepart) == mTimeTable.end()) {
			mTimeTable[ldepart] = vector<array<bool, 2>>(stations, { false, false });
		}
		mTimeTable[ldepart][0][RIGHT] = true;
		for (size_t t = 0; t < viTravel.size(); t++)
		{
			ldepart += viTravel[t];
			if (mTimeTable.find(ldepart) == mTimeTable.end()) {
				mTimeTable[ldepart] = vector<array<bool, 2>>(stations, { false, false });
			}
			mTimeTable[ldepart][t + 1][RIGHT] = true;
		}
	}

	for (auto rdepart : viRight)
	{
		if (mTimeTable.find(rdepart) == mTimeTable.end()) {
			mTimeTable[rdepart] = vector<array<bool, 2>>(stations, { false, false });
		}
		mTimeTable[rdepart][stations - 1][LEFT] = true;
		for (size_t t = viTravel.size(); t > 0; t--)
		{
			rdepart += viTravel[t - 1];
			if (mTimeTable.find(rdepart) == mTimeTable.end()) {
				mTimeTable[rdepart] = vector<array<bool, 2>>(stations, { false, false });
			}
			mTimeTable[rdepart][t - 1][LEFT] = true;
		}
	}
}

int calWaitingTime(
	const map<int, vector<array<bool, 2>>> &mTimeTable,
	const vector<int> &viTravel,
	int T)
{
	map<int, size_t> mTime;
	vector<int> viMoment;
	size_t stations = viTravel.size() + 1;
	for (auto iter = mTimeTable.begin(); iter != mTimeTable.end(); iter++)
	{
		mTime[iter->first] = viMoment.size();
		viMoment.push_back(iter->first);
	}
	vector<vector<int>> waiting(viMoment.size(), vector<int>(stations, INT_MAX));
	for (size_t mom = 0; mom < viMoment.size(); mom++)
	{
		waiting[mom][0] = viMoment[mom];
	}
	
	for (size_t mom = 0; mom < viMoment.size() - 1; mom++)
	{
		int now = viMoment[mom], stay = viMoment[mom + 1] - now;
		size_t nextMoment;
		for (size_t sta = 0; sta < stations; sta++)
		{
			if (waiting[mom][sta] == INT_MAX) continue;
			if (sta != stations - 1 && mTimeTable.at(now)[sta][RIGHT]) {
				nextMoment = mTime[now + viTravel[sta]];
				if (waiting[nextMoment][sta + 1] > waiting[mom][sta]) {
					waiting[nextMoment][sta + 1] = waiting[mom][sta];
				}
			}
			if (sta != 0 && mTimeTable.at(now)[sta][LEFT]) {
				nextMoment = mTime[now + viTravel[sta - 1]];
				if (waiting[nextMoment][sta - 1] > waiting[mom][sta]) {
					waiting[nextMoment][sta - 1] = waiting[mom][sta];
				}
			}
			if (waiting[mom + 1][sta] > waiting[mom][sta] + stay) {
				waiting[mom + 1][sta] = waiting[mom][sta] + stay;
			}
		}
	}
	
	for (size_t mom = viMoment.size(); mom > 0; mom--)
	{
		if (waiting[mom - 1][stations - 1] != INT_MAX && viMoment[mom - 1] <= T) {
			return T - viMoment[mom - 1] + waiting[mom - 1][stations - 1];
		}
	}
	return -1;
}

int main()
{
	int Test = 0;
	while (1) {
		int N = 0, T = 0, M1 = 0, M2 = 0;
		cin >> N;
		if (N == 0) break;
		cin >> T;
		vector<int> viTravel(N - 1, 0);
		for (int t = 0; t < N - 1; t++)
		{
			cin >> viTravel[t];
		}
		cin >> M1;
		vector<int> viLeft(M1, 0);
		for (int m = 0; m < M1; m++)
		{
			cin >> viLeft[m];
		}
		cin >> M2;
		vector<int> viRight(M2, 0);
		for (int m = 0; m < M2; m++)
		{
			cin >> viRight[m];
		}
		map<int, vector<array<bool, 2>>> mTimeTable;
		buildTimeTable(mTimeTable, viTravel, viLeft, viRight);
		int WaitingTime = calWaitingTime(mTimeTable, viTravel, T);
		cout << "Case Number " << ++Test << ": ";
		if (WaitingTime == -1)cout << "impossible" << endl;
		else cout << WaitingTime << endl;
	}
	return 0;
}
/*
4
55
5 10 15
4
0 5 10 20
4
0 5 10 15
4
18
1 2 3
5
0 3 6 10 12
6
0 3 5 7 12 15
2
30
20
1
20
7
1 3 5 7 11 13 17
0
*/
