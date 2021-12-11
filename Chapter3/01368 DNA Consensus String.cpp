#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

int main()
{
	int T = 0;
	cin >> T;
	char ch[4] = { 'A', 'C', 'G', 'T' };
	for (int t = 0; t < T; t++)
	{
		int m = 0, n = 0, distance = 0;
		cin >> m >> n;
		vector<string> vstrDNA(m, "");
		for (int i = 0; i < m; i++)
		{
			cin >> vstrDNA[i];
		}
		string strDNA;
		array<int, 4> arrCnt;
		for (int i = 0; i < n; i++)
		{
			arrCnt = { { 0, 0, 0, 0 } };
			for (int j = 0; j < m; j++)
			{
				if (vstrDNA[j][i] == 'A') arrCnt[0]++;
				else if (vstrDNA[j][i] == 'C') arrCnt[1]++;
				else if (vstrDNA[j][i] == 'G') arrCnt[2]++;
				else if (vstrDNA[j][i] == 'T') arrCnt[3]++;
			}
			int idx = 0;
			for (int k = 0; k < 4; k++)
			{
				if (arrCnt[k] > arrCnt[idx]) idx = k;
			}
			strDNA.push_back(ch[idx]);
			distance += m - arrCnt[idx];
		}
		cout << strDNA << endl << distance << endl;
	}
	return 0;
}
/*
3
5 8
TATGATAC
TAAGCTAC
AAAGATCC
TGAGATAC
TAAGATGT
4 10
ACGTACGTAC
CCGTACGTAG
GCGTACGTAT
TCGTACGTAA
6 10
ATGTTACCAT
AAGTTACGAT
AACAAAGCAA
AAGTTACCTT
AAGTTACCAA
TACTTACCAA
*/
