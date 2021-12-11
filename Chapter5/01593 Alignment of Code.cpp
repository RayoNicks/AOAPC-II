#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<vector<string>> lines;
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		string word;
		lines.push_back(vector<string>());
		while (iss >> word) {
			lines.back().push_back(word);
		}
	}
	vector<size_t> length;
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (j >= length.size()) {
				length.push_back(lines[i][j].length());
			}
			else if (lines[i][j].length() > length[j]) {
				length[j] = lines[i][j].length();
			}
			else;
		}
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			cout << lines[i][j];
			if (j != lines[i].size() - 1) {
				cout << string(length[j] - lines[i][j].length(), ' ');
				cout << ' ';
			}
		}
		cout << endl;
	}
	return 0;
}
/*
  start:  integer;    // begins here
stop: integer; //  ends here
 s:  string;
c:   char; // temp
*/
