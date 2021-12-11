#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

void push(vector<int> &viStack, vector<set<int>> &vecsetNum2Set)
{
	viStack.push_back(0);
	if (vecsetNum2Set.size() <= 0) vecsetNum2Set.push_back(set<int>());
}

void dup(vector<int> &viStack, vector<set<int>> &vecsetNum2Set)
{
	viStack.push_back(viStack.back());
}

void unionset(vector<int> &viStack, vector<set<int>> &vecsetNum2Set)
{
	int top = viStack.back();
	viStack.pop_back();
	int sec = viStack.back();
	viStack.pop_back();
	set<int> si = vecsetNum2Set[top];
	for (auto iter = vecsetNum2Set[sec].begin(); iter != vecsetNum2Set[sec].end(); iter++)
	{
		si.insert(*iter);
	}
	for (size_t idx = 0; idx < vecsetNum2Set.size(); idx++)
	{
		if (vecsetNum2Set[idx] == si){
			viStack.push_back(idx);
			return;
		}
	}
	viStack.push_back(vecsetNum2Set.size());
	vecsetNum2Set.push_back(si);
}

void intersect(vector<int> &viStack, vector<set<int>> &vecsetNum2Set)
{
	int top = viStack.back();
	viStack.pop_back();
	int sec = viStack.back();
	viStack.pop_back();
	set<int> &siTop = vecsetNum2Set[top], si;
	for (auto iter = siTop.begin(); iter != siTop.end(); iter++)
	{
		if (vecsetNum2Set[sec].find(*iter) != vecsetNum2Set[sec].end()){
			si.insert(*iter);
		}
	}
	for (size_t idx = 0; idx < vecsetNum2Set.size(); idx++)
	{
		if (vecsetNum2Set[idx] == si){
			viStack.push_back(idx);
			return;
		}
	}
	viStack.push_back(vecsetNum2Set.size());
	vecsetNum2Set.push_back(si);
}

void add(vector<int> &viStack, vector<set<int>> &vecsetNum2Set)
{
	int top = viStack.back();
	viStack.pop_back();
	int sec = viStack.back();
	viStack.pop_back();
	set<int> si = vecsetNum2Set[sec];
	si.insert(top);
	for (size_t idx = 0; idx < vecsetNum2Set.size(); idx++)
	{
		if (vecsetNum2Set[idx] == si){
			viStack.push_back(idx);
			return;
		}
	}
	viStack.push_back(vecsetNum2Set.size());
	vecsetNum2Set.push_back(si);
}

int main()
{
	int T = 0, ops = 0;
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		cin >> ops;
		string strOp;
		vector<int> viStack;
		vector<set<int>> vecsetNum2Set;
		for (int i = 0; i < ops; i++)
		{
			cin >> strOp;
			if (strOp == "PUSH"){
				push(viStack, vecsetNum2Set);
			}
			else if (strOp == "DUP"){
				dup(viStack, vecsetNum2Set);
			}
			else if (strOp == "UNION"){
				unionset(viStack, vecsetNum2Set);
			}
			else if (strOp == "INTERSECT"){
				intersect(viStack, vecsetNum2Set);
			}
			else if (strOp == "ADD"){
				add(viStack, vecsetNum2Set);
			}
			cout << vecsetNum2Set[viStack.back()].size() << endl;
		}
		cout << "***" << endl;
		//if (t == 42) return 0;
	}
	return 0;
}
/*
2
9
PUSH
DUP
ADD
PUSH
ADD
DUP
ADD
DUP
UNION
5
PUSH
PUSH
ADD
PUSH
INTERSECT
*/
