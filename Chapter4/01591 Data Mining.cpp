#include <iostream>
#include <climits>

using namespace std;

void cal(unsigned int N, unsigned long long SP, unsigned long long SQ,
	unsigned int& A, unsigned int &B, unsigned long long &K)
{
	K = ULLONG_MAX;
	unsigned long long k;
	for (unsigned int a = 0; a < 32; a++)
	{
		for (unsigned int b = 0; b < 32; b++)
		{
			if (((SP + (SP << a)) >> b) >= SQ){
				k = (((N - 1) * SP + (((N - 1) * SP) << a)) >> b) + SQ;
				if (k < K){
					K = (unsigned int)k;
					A = a;
					B = b;
				}
			}
		}
	}
}

int main()
{
	unsigned int N;
	unsigned long long SP, SQ;
	while (cin >> N >> SP >> SQ){
		unsigned int A = 0, B = 0;
		unsigned long long K = 0;
		cal(N, SP, SQ, A, B, K);
		cout << K << ' '<< A << ' ' << B << endl;
	}
	return 0;
}
/*
20 3 5
1024 7 1
*/
