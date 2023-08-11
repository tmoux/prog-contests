#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll l, r, m; cin >> l >> r >> m;
        ll mx = r-l;
        for (ll a = l; a <= r; a++) {
            ll mod = m % a;
            ll y = a-mod;
            if (mod <= mx && a <= m) {
                cout << a << ' ' << r << ' ' << r-mod << '\n';
                goto done;
            }
            if (y <= mx) {
                cout << a << ' ' << r-y << ' ' << r << '\n';
                goto done;
            }
        }

        done:;
    }
}
