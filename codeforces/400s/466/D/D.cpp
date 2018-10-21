#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 2005, M = 1e9+7;
int n, h;
ll dp[maxn][maxn];
int a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> h;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dp[1][0] = a[1] == h || a[1] + 1 == h ? 1 : 0;
    dp[1][1] = a[1] + 1 == h ? 1 : 0;

    for (int i = 2; i <= n + 1; i++) {
        for (int o = max(0,h-a[i]-1); o <= min(h - a[i],i); o++) {
            if (a[i] + o == h) {
                dp[i][o] = (dp[i][o] + dp[i-1][o]) % M;
                if (o) {
                    dp[i][o] = (dp[i][o] + dp[i-1][o-1]) % M;
                }
            }
            if (o + a[i] == h - 1) {
                dp[i][o] = (dp[i][o] + dp[i-1][o+1] * (o+1)) % M;
                dp[i][o] = (dp[i][o] + dp[i-1][o]) % M;
                dp[i][o] = (dp[i][o] + dp[i-1][o]*o) % M;
            }
        }
    }
    cout << dp[n][0] << '\n';

    return 0;
}

