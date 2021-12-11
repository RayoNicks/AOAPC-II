#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	int n = 0;
	while (cin >> n){
		cin.get();
		vector<string> vecstr;
		string strFile;
		size_t M = 0;
		for (int i = 0; i < n; i++)
		{
			cin >> strFile;
			if (strFile.size() > M) M = strFile.size();
			vecstr.push_back(strFile);
		}
		sort(vecstr.begin(), vecstr.end());
		//col * M + (col - 1) * 2 <= 60
		//col = 62 / (M + 2)
		size_t col = 62 / (M + 2);
		size_t row = vecstr.size() / col;
		if (row * col < vecstr.size()) row++;
		cout << "------------------------------------------------------------" << endl;
		for (size_t i = 0; i < row; i++)
		{
			cout << vecstr[i] << string(M - vecstr[i].size(), ' ');
			for (size_t j = 1; j < col; j++)
			{
				size_t idx = j * row + i;
				if (idx < vecstr.size()){
					cout << "  " << vecstr[idx] << string(M - vecstr[idx].size(), ' ');
				}
				else break;
			}
			cout << endl;
		}
	}
	return 0;
}
/*
10
tiny
2short4me
very_long_file_name
shorter
size-1
size2
size3
much_longer_name
12345678.123
mid_size_name
12
Weaser
Alfalfa
Stimey
Buckwheat
Porky
Joe
Darla
Cotton
Butch
Froggy
Mrs_Crabapple
P.D.
19
Mr._French
Jody
Buffy
Sissy
Keith
Danny
Lori
Chris
Shirley
Marsha
Jan
Cindy
Carol
Mike
Greg
Peter
Bobby
Alice
Ruben
*/
