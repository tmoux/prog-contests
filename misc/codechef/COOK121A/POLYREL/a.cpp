#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n; i++) {
            int x, y; cin >> x >> y;
        }
        ll ans = 0;
        while (n >= 3) {
            ans += n;
            n /= 2;
        }
        cout << ans << '\n';
    }
}
