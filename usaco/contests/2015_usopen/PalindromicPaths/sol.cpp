#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505, M = 1e9+7;
int N;
char g[maxn][maxn];
int dp[maxn][maxn];
void madd(int& a, int b) {
	a = (a+b) % M;
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> g[i][j];
		}
	}
	if (g[1][1] != g[N][N]) {
		cout << 0 << '\n';
		return 0;
	}
	
	return 0;
};