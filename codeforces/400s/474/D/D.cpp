#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5, M = 1e9+7;
int t, k, dp[maxn];
int pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> t >> k;
    dp[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        dp[i] = dp[i-1];
        if (i-k >= 0) dp[i] = (dp[i] + dp[i-k]) % M;
    }
    pre[0] = 1;
    for (int i = 1; i <= 100000; i++) {
        pre[i] = (dp[i] + pre[i-1]) % M;
    }
    while (t--) {
        int a, b; cin >> a >> b;
        int ans = (pre[b] - pre[a-1] + M) % M;
        cout << ans << '\n';
    }


    return 0;
}

