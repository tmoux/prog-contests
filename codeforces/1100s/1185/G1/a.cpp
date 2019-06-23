#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 16, M = 1e9+7;
int dp[1<<maxn][4];
int t[maxn], g[maxn];
int n, T;

int madd(int& a, int b) {
    a += b;
    if (a > M) a -= M;
}

int f(int mask, int last) {
    if (dp[mask][last] >= 0) return dp[mask][last];
    int ti = 0;
    for (int i = 0; i < n; i++) {
        if (mask&(1<<i)) ti += t[i];
    }
    if (ti == T) {
        return dp[mask][last] = 1;
    }
    else if (ti > T) {
        return dp[mask][last] = 0;
    }
    else {
        dp[mask][last] = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask&(1<<i)) && last != g[i]) {
                madd(dp[mask][last],f(mask|(1<<i),g[i])); 
            }
        }
        return dp[mask][last];
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> T;
    memset(dp,-1,sizeof dp);
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> g[i];
    }
    int ans = f(0,0);
    cout << ans << '\n';
}

