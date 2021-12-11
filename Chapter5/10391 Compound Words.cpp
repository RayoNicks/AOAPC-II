#include <iostream>
#include <set>
#include <string>

using namespace std;

int main()
{
	set<string> dict;
	string word;
	while (cin >> word) {
		dict.insert(word);
	}
	for (auto iter = dict.begin(); iter != dict.end(); iter++)
	{
		for (size_t i = 1; i < iter->length(); i++)
		{
			string former = iter->substr(0, i);
			string latter = iter->substr(i);
			if (dict.find(former) != dict.end() && dict.find(latter) != dict.end()) {
				cout << *iter << endl;
				break;
			}
		}
	}
	return 0;
}
/*
a
alien
born
less
lien
never
nevertheless
new
newborn
the
zebra
*/
