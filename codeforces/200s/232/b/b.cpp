#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int M = 1e9+7, maxn = 101;
int n, k;
ll m;
void madd(int& a, int b) {
	a += b;
	if (a >= M) a -= M;
}
int mult(int a, int b) {
	return (1LL*a*b) % M;
}
int modexp(int a, ll b) {
	int res = 1;
	while (b) {
		if (b&1LL) res = mult(res,a);
		a = mult(a,a);
		b /= 2;
	}
	return res;
}

int dp[maxn][maxn*maxn];
int ch[maxn][maxn];
int ways[maxn][2];

int main() {
	cin >> n >> m >> k;
	ch[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		ch[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			ch[i][j] = ch[i-1][j-1];
			madd(ch[i][j],ch[i-1][j]);
		}
	}
	for (int i = 0; i <= n; i++) {
		ways[i][0] = modexp(ch[n][i],m/n);
		ways[i][1] = mult(ways[i][0],ch[n][i]);
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n*n; j++) {
			for (int take = 0; take <= n && j-take >= 0; take++) {
				madd(dp[i][j],mult(ways[take][i-1<(m%n)],dp[i-1][j-take]));
			}
		}
	}
	cout << dp[n][k] << '\n';
}