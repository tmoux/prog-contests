#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 405, maxm = 250005;
int n, m, a[maxn];
const int INF = 2e9+9;
int dp[maxn][maxn][maxn]; //dp[l][r]

int main()
{
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) {
		scanf("%d",&a[i]);
	}

	for (int l = 1; l <= n; l++) {
		for (int r = l + 1; r <= n; r++) {
			dp[0][l][r] = a[r]-a[l];
		}
	}

	for (int k = 1; k <= n; k++) {
		for (int le = 1; le <= n; le++) {
			int t = le;
			for (int re = le + 1; re <= n; re++) {
				while (t < re && max(dp[k-1][le][t],a[re]-a[t]) > max(dp[k-1][le][t+1],a[re]-a[t+1])) {
					t++;
				}
				dp[k][le][re] = max(dp[k-1][le][t],a[re]-a[t]);
			}
		}
	}
	ll ans = 0;
	while (m--) {
		int s, f, c, r;
		scanf("%d %d %d %d",&s,&f,&c,&r);
		ans = max(ans,1LL*c*dp[r][s][f]);
	}
	cout << ans << '\n';

    return 0;
}
