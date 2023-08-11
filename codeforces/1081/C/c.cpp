#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005, M = 998244353;
int n, m, k;

ll dp[maxn][maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    dp[1][0] = m;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i+1][j] += dp[i][j];
            dp[i+1][j] %= M;
            dp[i+1][j+1] += 1LL*(m-1)*dp[i][j];
            dp[i+1][j+1] %= M;
        }
    }
    cout << dp[n][k] << endl;
}
