#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll n, r; cin >> n >> r;
        r = min(r,n);
        ll ans = ((1+r)*r)/2;
        if (r == n) {
            ans -= n-1;
        }
        cout << ans << '\n';
        /*
        if (r >= n) {
            ans -= (r-n+1)*(n-1);
        }
        cout << ans << '\n';
        */
    }
}
