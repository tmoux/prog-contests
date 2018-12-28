#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//solved 12/24/18, O(nk) dynamic programming solution
const int maxn = 30005, maxk = 505;
int dp[maxn][maxk], a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k, w; cin >> n >> k >> w;
        memset(dp,0,sizeof dp);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] += a[i-1];
        }
        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {
                int rr = dp[max(0,i-w)][j-1] + (a[i]-a[max(0,i-w)]);
                dp[i][j] = max(dp[i-1][j],rr);
            }
        }
        cout << dp[n][k] << '\n';
    }

    return 0;
}

