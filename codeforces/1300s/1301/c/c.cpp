#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ch2(ll x) {
    return (1LL*x*(x+1))/2;
}

void solve(ll n, ll m) {
    ll tot = ch2(n);
    ll n0 = n-m;
    ll ans = 0;
    int k = n0/(m+1);
    int extra = n0%(m+1);
    ans = extra*ch2(k+1)+(m+1-extra)*ch2(k);
    cout << (tot-ans) << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n, m; cin >> n >> m;
        solve(n,m);
    }
}

