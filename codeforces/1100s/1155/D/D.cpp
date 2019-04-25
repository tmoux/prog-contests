#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, x;
ll a[maxn];
ll dp[maxn][3];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> x;
    ll ans = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        dp[i][0] = max(max(dp[i-1][0]+a[i],a[i]),0LL);
        dp[i][1] = max(max(dp[i-1][0]+a[i]*x,dp[i-1][1]+a[i]*x),a[i]);
        dp[i][2] = max(max(dp[i-1][1]+a[i],dp[i-1][2]+a[i]),a[i]);
        ans = max(ans,max(dp[i][0],max(dp[i][1],dp[i][2])));
    }
    cout << ans << '\n';
}

