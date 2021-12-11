#include <iostream>
#include <queue>
#include <set>

using namespace std;

int main()
{
	priority_queue<long long> pq;
	set<long long> si;
	pq.push(-1);
	si.insert(-1);
	int cnt = 1;
	long long top;
	while (cnt <= 1500){
		top = -pq.top();
		pq.pop();
		if (si.find(-2 * top) == si.end()){
			pq.push(-2 * top);
			si.insert(-2 * top);
		}
		if (si.find(-3 * top) == si.end()){
			pq.push(-3 * top);
			si.insert(-3 * top);
		}
		if (si.find(-5 * top) == si.end()){
			pq.push(-5 * top);
			si.insert(-5 * top);
		}
		cnt++;
	}
	cout << "The 1500'th ugly number is " << top << '.' << endl;
	return 0;
}
