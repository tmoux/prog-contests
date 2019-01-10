#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

const int maxn = 1e5+5;
int n;
ll a[maxn];
string s;
ll dp[maxn][4];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> s;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i-1][0] + a[i] * (s[i-1] == 'h');
        dp[i][1] = min(dp[i-1][0],dp[i-1][1] + a[i] * (s[i-1] == 'a'));
        dp[i][2] = min(dp[i-1][1],dp[i-1][2] + a[i] * (s[i-1] == 'r'));
        dp[i][3] = min(dp[i-1][2],dp[i-1][3] + a[i] * (s[i-1] == 'd'));
    }
    ll ans = min(min(dp[n][0],dp[n][1]),min(dp[n][2],dp[n][3]));
    cout << ans << '\n';

    return 0;
}

