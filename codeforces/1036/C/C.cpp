#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll dp[20][2][4];
int digit[20];

ll f(int i, bool j, int k) {
    if (k < 0) return 0LL;
    if (i < 0) return 1LL;
    if (dp[i][j][k] >= 0) return dp[i][j][k];
    ll res = 0LL;
    if (j) {
        //restricted case
        int d = digit[i];
        if (d == 0) {
            res = f(i-1,j,k);
        }
        else {
            res = f(i-1,j,k-1);
            res += (d-1) * f(i-1,0,k-1);
            res += f(i-1,0,k);
        }
    }
    else {
        res = 9 * (f(i-1,j,k-1));
        res += f(i-1,0,k);
    }
    return dp[i][j][k] = res;
}

ll get(ll x) {
    ll orig = x;
    if (x == 0) return 1;
    memset(dp,-1,sizeof(dp));
    memset(digit,-1,sizeof(digit));
    int idx = 0;
    while (x) {
        digit[idx++] = x % 10;
        x /= 10;
    }
    return f(idx-1,1,3);
}

void solve() {
    ll l, r; cin >> l >> r;
    ll ans = get(r) - get(l-1);
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) solve();

    return 0;
}

