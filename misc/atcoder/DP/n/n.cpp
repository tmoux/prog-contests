#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 405;
int N, a[maxn];
ll pre[maxn];
ll dp[maxn][maxn];


ll f(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return dp[l][r] = 0;
    dp[l][r] = 1e18;
    for (int i = l; i < r; i++) {
        dp[l][r] = min(dp[l][r],(pre[i]-pre[l-1])+(pre[r]-pre[i])+f(l,i)+f(i+1,r));
    }
    return dp[l][r];
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) pre[i] = pre[i-1] + a[i];
    memset(dp,-1,sizeof dp);
    ll ans = f(1,N);
    cout << ans << '\n';
    return 0;
}

