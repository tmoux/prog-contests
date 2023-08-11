#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
ll dp[4][maxn];
ll h[2][maxn];
int n;

ll f(int mask, int i) {
    if (dp[mask][i] != -1) return dp[mask][i];
    if (i > n) return 0LL;
    dp[mask][i] = f(0,i+1);
    if (mask == 0 || mask == 2) dp[mask][i] = max(dp[mask][i],f(1,i+1)+h[0][i]);
    if (mask == 0 || mask == 1) dp[mask][i] = max(dp[mask][i],f(2,i+1)+h[1][i]);
    return dp[mask][i];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[0][i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> h[1][i];
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i <= n; i++) {
            dp[j][i] = -1;
        }
    }
    ll ans = f(0,1);
    cout << ans << '\n';
}

