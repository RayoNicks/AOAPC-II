#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
#include <set>
#include <vector>

using namespace std;

struct Topic
{
	int identifier;
	int number;
	int ElapsedTime;
	int ServiceTime;
	int SuccessiveTime;
};

istream& operator >> (istream &is, Topic &topic)
{
	is >> topic.identifier >> topic.number >> topic.ElapsedTime
		>> topic.ServiceTime >> topic.SuccessiveTime;
	return is;
}

struct Staff
{
	int identifier;
	vector<int> topics;
	int ReadyTime;
	int LastScheduled;
};

istream &operator >> (istream &is, Staff &staff)
{
	int n;
	is >> staff.identifier >> n;
	staff.topics.resize(n);
	for (int i = 0; i < n; i++)
	{
		is >> staff.topics[i];
	}
	staff.ReadyTime = 0;
	staff.LastScheduled = 0;
	return is;
}

map<int, vector<size_t>> SelectRequest(map<int, Topic> &RequestQueue, vector<Staff> &staffs, int current)
{
	map<int, vector<size_t>> selected;
	for (size_t i = 0; i < staffs.size(); i++)
	{
		if (staffs[i].ReadyTime <= current) {
			for (int TopicID : staffs[i].topics)
			{
				auto iter = RequestQueue.find(TopicID);
				if (iter != RequestQueue.end()) {
					if (RequestQueue[iter->first].number != 0 && iter->second.ElapsedTime <= current) {
						selected[TopicID].push_back(i);
						break;
					}
				}
			}
		}
	}
	return selected;
}

bool SolveConflict(map<int, Topic> &RequestQueue, vector<Staff> &staffs, int current,
	map<int, vector<size_t>> &selected, set<int> &SchedulingTime)
{
	bool conflict = false;
	for (auto iter = selected.begin(); iter != selected.end(); iter++)
	{
		vector<size_t> &ConflictStaffIndex = iter->second;
		int LastScheduled = staffs[ConflictStaffIndex.front()].LastScheduled;
		size_t index = 0;
		if (ConflictStaffIndex.size() > 1) {
			conflict = true;
			for (size_t i = 1; i < ConflictStaffIndex.size(); i++)
			{
				if (staffs[ConflictStaffIndex[i]].LastScheduled < LastScheduled) {
					LastScheduled = staffs[ConflictStaffIndex[i]].LastScheduled;
					index = i;
				}
			}
		}
		Topic &topic = RequestQueue[iter->first];
		Staff &staff = staffs[ConflictStaffIndex[index]];
		staff.LastScheduled = current;
		staff.ReadyTime = current + RequestQueue[iter->first].ServiceTime;
		SchedulingTime.insert(staff.ReadyTime);
		if (--topic.number != 0) {
			topic.ElapsedTime += topic.SuccessiveTime;
		}
		else {
			RequestQueue.erase(iter->first);
		}
	}
	return conflict;
}

int GetNextRequestTime(const map<int, Topic> &RequestQueue, int current)
{
	int time = INT_MAX;
	for (auto iter = RequestQueue.begin(); iter != RequestQueue.end(); iter++)
	{
		if (current < iter->second.ElapsedTime && iter->second.ElapsedTime < time) {
			time = iter->second.ElapsedTime;
		}
	}
	return time;
}

int ServiceTime(map<int, Topic> &RequestQueue, vector<Staff> &staffs)
{
	set<int> SchedulingTime;
	int current = 0;
	SchedulingTime.insert(current);
	while (!SchedulingTime.empty()) {
		current = *SchedulingTime.begin();
		SchedulingTime.erase(SchedulingTime.begin());
		bool conflict = true;
		while (conflict) {
			map<int, vector<size_t>> selected = SelectRequest(RequestQueue, staffs, current);
			if (selected.empty()) break;
			conflict = SolveConflict(RequestQueue, staffs, current, selected, SchedulingTime);
		}
		if (RequestQueue.empty()) break;
		int NextRequestTime = GetNextRequestTime(RequestQueue, current);
		if (NextRequestTime != INT_MAX) {
			SchedulingTime.insert(NextRequestTime);
		}
	}
	return *SchedulingTime.rbegin();
}

int main()
{
	int request, personnel, scenario = 1;
	while (cin >> request) {
		if (request == 0) break;
		map<int, Topic> RequestQueue;
		vector<Staff> staffs;
		for (int i = 0; i < request; i++)
		{
			Topic topic;
			cin >> topic;
			RequestQueue[topic.identifier] = topic;
		}
		cin >> personnel;
		for (int i = 0; i < personnel; i++)
		{
			staffs.push_back(Staff());
			cin >> staffs.back();
		}
		sort(staffs.begin(), staffs.end(), [](const Staff &a, const Staff &b)
		{
			return a.identifier < b.identifier;
		});
		cout << "Scenario " << scenario++ << ": All requests are serviced within "
			<< ServiceTime(RequestQueue, staffs) << " minutes." << endl;
	}
	return 0;
}
/*
3
128 20 0 5 10
134 25 5 6 7
153 30 10 4 5
4
10 2 128 134
11 1 134
12 2 128 153
13 1 153
0
*/
