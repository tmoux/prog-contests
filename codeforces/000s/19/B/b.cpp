#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2005;
int n;

ll dp[maxn][maxn];
int t[maxn], c[maxn];
const ll INF = 1e18;

ll f(int i, int j) {
    if (j >= n) return 0;
    if (i >= n) return INF;
    ll& res = dp[i][j];
    if (res != -1) return res;
    res = f(i+1,j);
    res = min(res,c[i]+f(i+1,j+1+t[i]));
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    memset(dp,-1,sizeof dp);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> t[i] >> c[i];
    }
    ll ans = f(0,0);
    cout << ans << '\n';
}

