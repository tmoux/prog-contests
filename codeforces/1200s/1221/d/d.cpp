#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
const ll INF = 1LL<<62;
int n;
ll a[maxn], b[maxn];

ll dp[3][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i];
        }
        dp[0][0] = 0;
        dp[1][0] = b[0];
        dp[2][0] = 2*b[0];
        for (int i = 1; i < n; i++) {
            dp[0][i] = dp[1][i] = dp[2][i] = INF;
            for (int k = 0; k < 3; k++) {
                for (int j = 0; j < 3; j++) {
                    if (a[i-1]+j != a[i]+k)
                        dp[k][i] = min(dp[k][i],dp[j][i-1] + k*b[i]);
                }
            }
        }
        ll ans = min(dp[0][n-1],min(dp[1][n-1],dp[2][n-1]));
        cout << ans << '\n';
    }
}

