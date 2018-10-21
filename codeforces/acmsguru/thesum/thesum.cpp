#include <iostream>
using namespace std;

int main()
{
	int k; cin >> k;
	int fib[100], pfx[100];
	fib[2] = 1, fib[1] = 1;
	for (int i = 3; i <= k; i++) {
		fib[i] = fib[i-1] + fib[i-2];
	}
	pfx[1] = fib[1];
	for (int i = 2; i <= k; i++) {
			pfx[i] = pfx[i-1] + fib[i];
	}
	cout << pfx[k] << '\n';
}
/*
for (int i = 0; i < N; i++) {
for (int j = 0; j < N; j++) {
for (int i = 0; i < N: i++) {
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {

        }
    }
}
		}
}
*/
