#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int d, m;
int M;

void madd(ll& a, ll b) {
    a = (a+b) % M;
}
ll mult(ll a, ll b) {
    return (1LL*a*b) % M;
}

ll dp[33][33];

ll cnt(int j) {
    if ((1LL<<j) > d) return 0;
    else if ((1LL<<(j+1) > d)) return d - (1LL<<j) + 1;
    else return 1LL<<j;
}

ll f(int i, int j) {
    ll& res = dp[i][j];
    if (res != -1) return res;
    if (i == 0) {
        return res = cnt(j);
    }
    res = 0;
    for (int k = 0; k < j; k++) {
        madd(res,f(i-1,k));
    }
    ll count = cnt(j);
    res = mult(res,count);
    return res;
}

void solve() {
    cin >> d >> m;
    M = m; 
    memset(dp,-1,sizeof dp);
    ll ans = 0;
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 33; j++) {
            madd(ans,f(i,j));
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

