#include <iostream>
#include <vector>
#include <string>

#define DR 0
#define DC 1
#define IR 2
#define IC 3
#define EX 4

using namespace std;

void delRow(const vector<int> &viOps, int &r)
{
	int del = 0;
	for (size_t i = 1; i < viOps.size(); i++)
	{
		if (viOps[i] < r) del++;
		else if (viOps[i] == r){
			r = 0;
			return;
		}
	}
	r -= del;
}

void delCol(const vector<int> &viOps, int &c)
{
	int del = 0;
	for (size_t i = 1; i < viOps.size(); i++)
	{
		if (viOps[i] < c) del++;
		else if (viOps[i] == c){
			c = 0;
			return;
		}
	}
	c -= del;
}

void addRow(const vector<int> &viOps, int &r)
{
	int add = 0;
	for (size_t i = 1; i < viOps.size(); i++)
	{
		if (viOps[i] <= r) add++;
	}
	r += add;
}

void addCol(const vector<int> &viOps, int &c)
{
	int add = 0;
	for (size_t i = 1; i < viOps.size(); i++)
	{
		if (viOps[i] <= c) add++;
	}
	c += add;
}

void exchg(const vector<int> &viOps, int &r, int &c)
{
	if (viOps[1] == r && viOps[2] == c){
		r = viOps[3];
		c = viOps[4];
	}
	else if (viOps[3] == r && viOps[4] == c){
		r = viOps[1];
		c = viOps[2];
	}
}

void track(const int cnt, const int row, const int col, const vector<vector<int>> &vviOps)
{
	cout << "Spreadsheet #" << cnt << endl;
	int r, c, track = 0;
	cin >> track;
	for (int i = 0; i < track; i++)
	{
		cin >> r >> c;
		cout << "Cell data in (" << r << ',' << c << ") ";
		for (auto iter = vviOps.begin(); iter != vviOps.end(); iter++)
		{
			const vector<int> &viOps = *iter;
			switch (viOps[0])
			{
			case DR:
				delRow(viOps, r);
				break;
			case DC:
				delCol(viOps, c);
				break;
			case IR:
				addRow(viOps, r);
				break;
			case IC:
				addCol(viOps, c);
				break;
			case EX:
				exchg(viOps, r, c);
				break;
			}
			if (r == 0 || c == 0) break;
		}
		if (r == 0 || c == 0){
			cout << "GONE" << endl;
		}
		else{
			cout << "moved to (" << r << ',' << c << ')' << endl;
		}
	}
}

int main()
{
	int r = 0, c = 0, op = 0, cnt = 0;
	while (cin >> r >> c){
		if (r == 0 && c == 0) break;
		if (cnt != 0) cout << endl;
		cin >> op;
		vector<vector<int>> vviOps(op, vector<int>());
		string strOp;
		int num = 0, r1, c1, r2, c2;
		for (int i = 0; i < op; i++)
		{
			cin >> strOp;
			if (strOp == "EX"){
				vviOps[i].push_back(EX);
				cin >> r1 >> c1 >> r2 >> c2;
				vviOps[i].push_back(r1);
				vviOps[i].push_back(c1);
				vviOps[i].push_back(r2);
				vviOps[i].push_back(c2);
			}
			else if (strOp[1] == 'R'){
				if (strOp[0] == 'D') vviOps[i].push_back(DR);
				else vviOps[i].push_back(IR);
				cin >> num;
				for (int j = 0; j < num; j++)
				{
					cin >> r1;
					vviOps[i].push_back(r1);
				}
			}
			else if (strOp[1] == 'C'){
				if (strOp[0] == 'D') vviOps[i].push_back(DC);
				else vviOps[i].push_back(IC);
				cin >> num;
				for (int j = 0; j < num; j++)
				{
					cin >> c1;
					vviOps[i].push_back(c1);
				}
			}
		}
		track(++cnt, r, c, vviOps);
	}
	return 0;
}
/*
7 9
5
DR 2 1 5
DC 4 3 6 7 9
IC 1 3
IR 2 2 4
EX 1 2 6 5
4
4 8
5 5
7 8
6 5
0 0
*/
