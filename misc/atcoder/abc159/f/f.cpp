#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3005, M = 998244353;
int n, s;
ll a[maxn];

void madd(ll& a, ll b) {
    a += b;
    a %= M;
}

ll dp[maxn][maxn][3];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dp[1][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= s; j++) {
            madd(dp[i+1][j][0],dp[i][j][0]);
            madd(dp[i+1][j][1],(dp[i][j][0]+dp[i][j][1])%M);
            madd(dp[i+1][j][2],(dp[i][j][0]+dp[i][j][1]+dp[i][j][2])%M);
            if (j+a[i] <= s) {
                madd(dp[i+1][j+a[i]][1],(dp[i][j][0]+dp[i][j][1])%M);
                madd(dp[i+1][j+a[i]][2],(dp[i][j][0]+dp[i][j][1])%M);
            }
        }
    }
    ll ans = dp[n+1][s][2];
    cout << ans << '\n';
}

