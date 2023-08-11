#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, q; cin >> n >> q;
        vector<ll> a(n+1,0);
        while (q--) {
            int tt; cin >> tt;
            if (tt == 1) {
                int x, y; cin >> x >> y;
                a[x] = y;
            }
            else {
                int l, r; cin >> l >> r;
                ll ans = 0;
                for (int i = l; i <= r; i++) {
                    ans += a[i];
                }
                cout << ans << '\n';
            }
        }
    }
}

