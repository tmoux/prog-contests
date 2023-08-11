#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        ll ans = 0;
        ll mult = 1;
        auto calc = [&n](ll mult) {
            return n/mult;
        };
        while (calc(mult) > 0) {
            ans += calc(mult);
            mult *= 2;
        }
        cout << ans << '\n';
    }
}
