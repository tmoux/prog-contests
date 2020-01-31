#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, k;

ll check(ll g) {
    ll d = n/g;
    return k*(k+1)/2 > d ? -1 : g;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        ll s = k*(k+1)/2;
        if (s > n) {
            cout << -1 << '\n';
            continue;
        }
        ll ans = -1;
        for (ll i = 1; i*i <= n; i++) {
            if (n % i == 0) {
                ans = max(ans,check(i));
                ans = max(ans,check(n/i));
            }
        }
        cout << ans << '\n';
    }
}

