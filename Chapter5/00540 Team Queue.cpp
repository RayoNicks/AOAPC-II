#include <iostream>
#include <deque>
#include <map>
#include <string>
#include <sstream>

using namespace std;

void enqueue(deque<deque<int>> &TeamQueue, const int element, const map<int, int> &miiTeam)
{
	for (size_t i = 0; i < TeamQueue.size(); i++)
	{
		if (miiTeam.at(TeamQueue[i][0]) == miiTeam.at(element)){
			TeamQueue[i].push_back(element);
			return;
		}
	}
	TeamQueue.push_back(deque<int>(1, element));
}

void dequeue(deque<deque<int>> &TeamQueue)
{
	int i = TeamQueue.front().front();
	TeamQueue.front().pop_front();
	if (TeamQueue.front().size() == 0) TeamQueue.pop_front();
	cout << i << endl;
}

int main()
{
	int team = 0, scenario = 1;
	while (1){
		cin >> team;
		if (team == 0) break;
		cin.get();
		map<int, int> miiTeam;
		string strTeam;
		int element;
		for (int t = 0; t < team; t++)
		{
			int num = 0;
			cin >> num;
			for (int n = 0; n < num; n++)
			{
				cin >> element;
				miiTeam[element] = t;
			}
		}
		cout << "Scenario #" << scenario++ << endl;
		deque<deque<int>> TeamQueue;
		string strOps;
		while (getline(cin, strOps)){
			if (strOps[0] == 'S') break;
			else if (strOps[0] == 'E'){
				element = stol(strOps.substr(8));
				enqueue(TeamQueue, element, miiTeam);
			}
			else if (strOps[0] == 'D'){
				dequeue(TeamQueue);
			}
		}
		cout << endl;
	}
	return 0;
}
/*
2
3 101 102 103
3 201 202 203
ENQUEUE 101
ENQUEUE 201
ENQUEUE 102
ENQUEUE 202
ENQUEUE 103
ENQUEUE 203
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
2
5 259001 259002 259003 259004 259005
6 260001 260002 260003 260004 260005 260006
ENQUEUE 259001
ENQUEUE 260001
ENQUEUE 259002
ENQUEUE 259003
ENQUEUE 259004
ENQUEUE 259005
DEQUEUE
DEQUEUE
ENQUEUE 260002
ENQUEUE 260003
DEQUEUE
DEQUEUE
DEQUEUE
DEQUEUE
STOP
0
*/
