#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

typedef long long ll;
const int LMAX = 1000005;
int memo[LMAX];
int counter[LMAX][10];
int f(int n) {
	int prod = 1;
	while (n > 0) {
		if (n % 10 != 0) {
			prod *= n%10;
		}
		n /= 10;
	}
	return prod;
}
int g(int n) {
	if (memo[n] != 0) {
		return memo[n];
	}
	if (n < 10) {
		return memo[n] = n;
	}
	return memo[n] = g(f(n));
}

void processQuery(int l, int r, int k) {
	cout << counter[r][k]-counter[l-1][k] << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	//adding this line had 3x speedup for Q=200000 case!
	//freopen("input.in","r",stdin);
	int Q; cin >> Q;
	for (int i = 1; i < LMAX; i++) {
		for (int j = 1; j <= 9; j++) {
			counter[i][j] = counter[i-1][j];
		}
		counter[i][g(i)]++;
	}
	for (int i = 0; i < Q; i++) {
		int l, r, k; cin >> l >> r >> k;
		processQuery(l,r,k);
	}

	return 0;
}