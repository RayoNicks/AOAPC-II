#include <iostream>
#include <string>
#include <map>
#include <iomanip>

using namespace std;

int main()
{
	map<int, double> mid;
	mid['C'] = 12.01;
	mid['H'] = 1.008;
	mid['O'] = 16.00;
	mid['N'] = 14.01;
	int n = 0;
	cin >> n;
	string strOrgCom;
	for (int i = 0; i < n; i++)
	{
		cin >> strOrgCom;
		double mass = 0.0;
		auto iter = strOrgCom.begin();
		while (iter != strOrgCom.end()){
			if (mid.find(*iter) != mid.end()){
				if (iter + 1 != strOrgCom.end() && isdigit(*(iter + 1))){
					//C¡¢H¡¢O¡¢NÔªËØ
					int len = 2;
					while (iter + len < strOrgCom.end() && isdigit(*(iter + len))) len++;
					mass += mid[*iter] * stod(string(iter + 1, iter + len));
					iter += len;
				}
				else{
					mass += mid[*iter];
					iter++;
				}
			}
		}
		cout << fixed << setprecision(3) << mass << endl;
	}
	return 0;
}
/*
4
C
C6H5OH
NH2CH2COOH
C12H22O11
*/
