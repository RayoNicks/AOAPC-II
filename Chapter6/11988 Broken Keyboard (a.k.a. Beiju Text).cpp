#include <iostream>
#include <list>
#include <string>

using namespace std;

int main()
{
	string line;
	while (cin >> line) {
		list<char> text;
		list<char>::iterator InsertIter = text.end();
		for (char ch : line)
		{
			if (ch == '[') {
				InsertIter = text.begin();
			}
			else if (ch == ']') {
				InsertIter = text.end();
			}
			else {
				text.insert(InsertIter, ch);
			}
		}
		for (char ch : text)
		{
			cout << ch;
		}
		cout << endl;
	}
	return 0;
}
/*
This_is_a_[Beiju]_text
[[]][][]Happy_Birthday_to_Tsinghua_University
*/
