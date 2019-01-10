#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3005;
int N, a[maxn];
ll dp[2][maxn][maxn];

ll f(int t, int l, int r) {
    if (dp[t][l][r] != -1) return dp[t][l][r];
    if (l > r) return dp[t][l][r] = 0;
    if (t == 0) {
        return dp[t][l][r] = max(f(!t,l+1,r) + a[l],
                                 f(!t,l,r-1) + a[r]);
    }
    else {
        return dp[t][l][r] = min(f(!t,l+1,r) - a[l],
                                 f(!t,l,r-1) - a[r]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    memset(dp,-1,sizeof dp);
    ll ans = f(0,1,N);
    cout << ans << '\n';
    return 0;
}

