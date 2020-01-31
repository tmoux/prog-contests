#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll d, ll x) {
    return x + (d+x)/(x+1);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n, d; cin >> n >> d;
        ll s = (ll)sqrt(d);
        ll mn = 1e18;
        for (ll x = max(0LL,s-1000); x <= s+1000; x++) {
            mn = min(mn,f(d,x));
        }
        cout << (mn <= n ? "YES" : "NO") << '\n';
    }
}

