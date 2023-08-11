#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M1 = 1e9+7, maxn = 105;
int n, a[maxn], dp[2][maxn][maxn*maxn], comb[maxn][maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    map<int,int> cnt;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ++cnt[a[i]];
    }
    if (cnt.size() <= 2) {
        cout << n << '\n';
        return 0;
    }
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j <= i; j++) {
            if (j == 0) comb[i][j] = 1;
            else comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % M1;
        }
    }

    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k < maxn*maxn; k++) {
                dp[1][j][k] = (dp[0][j][k] + (k-a[i]>=0&&j-1>=0?dp[0][j-1][k-a[i]]:0)) % M1;
            }
        }
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k < maxn*maxn; k++) {
                dp[0][j][k] = dp[1][j][k];
            }
        }
    }
   
    int ans = 0;
    for (auto& p: cnt) {
        int c = p.first;
        int cnt = p.second;
        int r = 0;
        for (int i = 1; i <= cnt; i++) {
            int expect = comb[cnt][i];
            int lget = dp[0][i][i*c];
            if (expect == lget) {
                r = i;
            }
        }
        ans = max(ans,r);
    }
    cout << ans << '\n';

    return 0;
}
