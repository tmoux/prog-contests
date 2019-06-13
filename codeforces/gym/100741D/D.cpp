#include <iostream>
using namespace std;
int xorsum = 0, ai, N;
int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> ai;
		xorsum ^= ai;
	}
	printf("%d\n",xorsum);	
	return 0;
}