#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 3e5+5, maxk = 100;
int n, dp[maxk][maxn], a[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    freopen("248.in","r",stdin); freopen("248.out","w",stdout);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; 
    }
    int res = 0;
    for (int k = 1; k < maxk; k++) {
        for (int i = 1; i <= n; i++) {
            if (a[i] == k) {
                dp[k][i] = i+1;
            }
            else {
                if (dp[k-1][i] && dp[k-1][dp[k-1][i]]) {
                    dp[k][i] = dp[k-1][dp[k-1][i]];
                }
            }
            if (dp[k][i] > 0) {
                res = max(res,k);
            }
        }
    }
    cout << res << '\n';

    return 0;
}

