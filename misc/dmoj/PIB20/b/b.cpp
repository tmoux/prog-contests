#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll T; cin >> T;
    ll lo = 0, hi = 1e18;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        if (mid/2-mid/7 <= T) {
            lo = mid;
        }
        else hi = mid;
    }
    ll ans = lo;
    for (ll x = lo; x <= lo+10000; x++) {
        if (x/2-x/7 <= T) ans = x;
    }
    cout << ans << '\n';
}
