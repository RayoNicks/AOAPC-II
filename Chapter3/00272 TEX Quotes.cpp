#include <iostream>

using namespace std;

int main()
{
	bool bLeft = true;
	char c = 0;
	while (cin.get(c)){
		if (c == '"'){
			if (bLeft){
				cout << "``";
			}
			else{
				cout << "''";
			}
			bLeft = !bLeft;
		}
		else{
			cout << c;
		}
	}
	return 0;
}
/*
"To be or not to be," quoth the Bard, "that
is the question".
The programming contestant replied: "I must disagree.
To `C' or not to `C', that is The Question!"
*/
