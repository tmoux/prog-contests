#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll r; cin >> r;
    ll ans = 0;
    for (ll x = -r; x <= r; x++) {
        ll a = r*r-x*x;
        double hi = floor(sqrt(a));
        double lo = ceil(-sqrt(a));
        ans += hi-lo+1;
    }
    cout << ans << '\n';
}

