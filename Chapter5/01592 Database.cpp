#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void checkPNF(const vector<vector<size_t>> &db)
{
	for (size_t c1 = 0; c1 < db[0].size(); c1++)
	{
		for (size_t c2 = c1 + 1; c2 < db[0].size(); c2++)
		{
			map<pair<size_t, size_t>, int> mCol2Row;
			for (size_t r = 0; r < db.size(); r++)
			{
				pair<size_t, size_t> p(db[r][c1], db[r][c2]);
				auto iter = mCol2Row.find(p);
				if (iter != mCol2Row.end()){
					cout << "NO" << endl;
					cout << iter->second << ' ' << r + 1 << endl;
					cout << c1 + 1 << ' ' << c2 + 1<< endl;
					return;
				}
				else{
					mCol2Row[p] = r + 1;
				}
			}

		}
	}
	cout << "YES" << endl;
}

int main()
{
	int n, m;
	while (cin >> n >> m){
		cin.get();
		string strLine;
		size_t ID = 1;
		map<string, size_t> mStr2ID;
		vector<vector<size_t>> db(n, vector<size_t>(m, 0));
		for (int i = 0; i < n; i++)
		{
			getline(cin, strLine);
			strLine.push_back(',');
			string::size_type begin = 0, pos, j = 0;
			string strData;
			while ((pos = strLine.find(',', begin)) != string::npos){
				strData = strLine.substr(begin, pos - begin);
				if (mStr2ID.find(strData) == mStr2ID.end()){
					mStr2ID[strData] = ID++;
				}
				db[i][j] = mStr2ID[strData];
				begin = pos + 1;
				j++;
			}
		}
		checkPNF(db);
	}
	return 0;
}
/*
3 3
How to compete in ACM ICPC,Peter,peter@neerc.ifmo.ru
How to win ACM ICPC,Michael,michael@neerc.ifmo.ru
Notes from ACM ICPC champion,Michael,michael@neerc.ifmo.ru
2 3
1,Peter,peter@neerc.ifmo.ru
2,Michael,michael@neerc.ifmo.ru
*/
