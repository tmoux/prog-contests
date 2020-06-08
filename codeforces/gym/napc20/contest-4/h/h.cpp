#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 305;
int n, x[maxn], y[maxn];
bool adj[maxn][maxn];
double dp[maxn][maxn][2];
double dist(int i, int j) {
	return hypot(x[i]-x[j],y[i]-y[j]);
}
double d[maxn][maxn];

int nxt(int i) {
	return i==n-1?0:i+1;
}

double f(int i, int j, int which) {
	double& res = dp[i][j][which];
	if (res > -0.5) return res;
	res = 0;
	for (int k = (i+1)%n; k != j; k = (k+1)%n) {
		if (which==0&&adj[i][k]) {
			res = max(res,d[i][k]+f(k,j,0));
			res = max(res,d[i][k]+f(i,k,1));
		}
		else if (which==1&&adj[j][k]) {
			res = max(res,d[j][k]+f(k,j,0));
			res = max(res,d[j][k]+f(i,k,1));
		}
	}
	//printf("[%d][%d][%d]: %.3f\n",i,j,which,res);
	return res;
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < 2; k++) {
				dp[i][j][k] = -1.0;
			}
			adj[i][j] = false;
			d[i][j] = dist(i,j);
		}
	}
	int m; cin >> m;
	while (m--) {
		int a, b; cin >> a >> b;
		--a; --b;
		adj[a][b] = adj[b][a] = true;
	}
	double ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adj[i][j]) {
				ans = max(ans,dist(i,j)+f(i,j,0));
				ans = max(ans,dist(i,j)+f(i,j,1));
			}
		}
	}
	cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
	//ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--) solve();
}
