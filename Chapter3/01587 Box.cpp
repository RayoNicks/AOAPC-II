#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Rect
{
	int width;
	int height;
}Rect;

bool operator<(const Rect &r1, const Rect &r2)
{
	if (r1.width < r2.width) return true;
	else if (r1.width == r2.width){
		if (r1.height < r2.height) return true;
		else return false;
	}
	else return false;
}

bool operator==(const Rect &r1, const Rect &r2)
{
	return r1.width == r2.width && r1.height == r2.height;
}

int main()
{
	vector<Rect> vecRec;
	string strLine;
	Rect rect;
	while (cin >> rect.width >> rect.height){
		if (rect.width > rect.height){
			rect.width ^= rect.height ^= rect.width ^= rect.height;
		}
		vecRec.push_back(rect);
		if (vecRec.size() == 6){
			sort(vecRec.begin(), vecRec.end());
			bool bPossible = false;
			if (vecRec[0] == vecRec[1] && vecRec[2] == vecRec[3] && vecRec[4] == vecRec[5]){
				if (vecRec[0].width == vecRec[2].width &&
					vecRec[0].height == vecRec[4].width &&
					vecRec[2].height == vecRec[4].height) bPossible = true;
			}
			if (bPossible) cout << "POSSIBLE" << endl;
			else cout << "IMPOSSIBLE" << endl;
			vecRec.clear();
		}
	}
	return 0;
}
/*
1345 2584
2584 683
2584 1345
683 1345
683 1345
2584 683
1234 4567
1234 4567
4567 4321
4322 4567
4321 1234
4321 1234
*/
