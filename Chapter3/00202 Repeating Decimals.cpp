#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int a = 0, b = 0;
	while (cin >> a >> b){
		cout << a << '/' << b << " = ";
		vector<size_t> viR(b, -1);
		vector<int> viQ;
		viQ.push_back(a / b);
		while (1){
			a %= b;
			if (viR[a] != -1){
				break;
			}
			else{
				viR[a] = viQ.size();
				a *= 10;
				viQ.push_back(a / b);
			}
		}
		cout << viQ[0] << '.';
		int len = viQ.size() - viR[a], up = 50;
		size_t idx = 0;
		for (idx = 1; idx < viR[a]; idx++)
		{
			cout << viQ[idx];
			up--;
		}
		cout << '(';
		for (; idx < viQ.size() && idx < viR[a] + up; idx++)
		{
			cout << viQ[idx];
		}
		if (idx != viQ.size()){
			cout << "...)" << endl;
		}
		else cout << ")" << endl;
		cout << "   " << len << " = number of digits in repeating cycle" << endl << endl;
	}
	return 0;
}
/*
76 25
5 43
1 397
*/
