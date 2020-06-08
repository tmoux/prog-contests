#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 101;
int n, a[maxn];
int m;
pair<char,int> b[maxn];

int dp[1<<20];

int f(int mask) {
	if (dp[mask] != -1) return dp[mask];
	int i = __builtin_popcount(mask);
	if (i == m) return dp[mask] = 0;
	if (b[i].first == 'p') {
		int j = 0;
		for (; j < m; j++) {
			if (!(mask & (1<<j))) break;
		}
		if (b[i].second == 1) return dp[mask] = a[j]+f(mask|(1<<j));
		else return dp[mask] = -a[j]+f(mask|(1<<j));
	}
	else {
		if (b[i].second == 1) {
			dp[mask] = -2e9;
			for (int j = 0; j < m; j++) {
				if (!(mask & (1<<j))) {
					dp[mask] = max(dp[mask],f(mask|(1<<j)));
				}
			}
		}
		else {
			dp[mask] = 2e9;
			for (int j = 0; j < m; j++) {
				if (!(mask & (1<<j))) {
					dp[mask] = min(dp[mask],f(mask|(1<<j)));
				}
			}
		}
		return dp[mask];
	}
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a,a+n,greater<int>());
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> b[i].first >> b[i].second;
	}
	memset(dp,-1,sizeof dp);
	cout << f(0) << '\n';
}

