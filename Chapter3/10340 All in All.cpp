#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str1, str2;
	while (cin >> str1 >> str2){
		bool bFind = false;
		for (size_t i = 0; i < str2.size(); i++)
		{
			if (str2[i] == str1[0]){
				size_t k = 1;
				for (size_t j = i + 1; j < str2.size() && k < str1.size(); j++)
				{
					if (str2[j] == str1[k]) k++;
				}
				if (k == str1.size()){
					bFind = true;
					break;
				}
			}
		}
		if (bFind) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	return 0;
}
/*
sequence subsequence
person compression
VERDI vivaVittorioEmanueleReDiItalia
caseDoesMatter CaseDoesMatter
*/
