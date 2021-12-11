#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void ConstructDictionary(map<string, string> &dict)
{
	string line, key, value;
	cin >> line;
	for (char &ch : line)
	{
		if (!isalnum(ch)) ch = ' ';
	}
	stringstream ss(line);
	while (ss >> key >> value) {
		dict[key] = value;
	}
}

void OutputChanges(const vector<string> &change, char prefix)
{
	if (change.empty()) return;
	cout << prefix;
	for (size_t i = 0; i < change.size(); i++)
	{
		if (i != 0) cout << ',';
		cout << change[i];
	}
	cout << endl;
}

void diff(const map<string, string> &dict1, const map<string, string> &dict2)
{
	vector<string> add, remove, change;
	for (auto iter1 = dict1.begin(); iter1 != dict1.end(); iter1++)
	{
		auto iter2 = dict2.find(iter1->first);
		if (iter2 == dict2.end()) {
			remove.push_back(iter1->first);
		}
		else {
			if (iter1->second != iter2->second) {
				change.push_back(iter1->first);
			}
		}
	}
	for (auto iter2 = dict2.begin(); iter2 != dict2.end(); iter2++)
	{
		auto iter1 = dict1.find(iter2->first);
		if (iter1 == dict1.end()) {
			add.push_back(iter2->first);
		}
	}
	if (add.empty() && remove.empty() && change.empty()) {
		cout << "No changes\n" << endl;
	}
	else {
		OutputChanges(add, '+');
		OutputChanges(remove, '-');
		OutputChanges(change, '*');
		cout << endl;
	}
}

int main()
{
	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		map<string, string> dict1, dict2;
		ConstructDictionary(dict1);
		ConstructDictionary(dict2);
		diff(dict1, dict2);
	}
	return 0;
}
/*
3
{a:3,b:4,c:10,f:6}
{a:3,c:5,d:10,ee:4}
{x:1,xyz:123456789123456789123456789}
{xyz:123456789123456789123456789,x:1}
{first:1,second:2,third:3}
{third:3,second:2}
*/
