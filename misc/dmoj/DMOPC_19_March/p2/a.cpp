#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll calc(ll p, ll b) {
    ll ans = 0;
    ll m = p;
    while (b/p > 0) {
        ans += b/p;
        p *= m;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b; cin >> a >> b;
    ll cp = a;
    ll ans = 1e18;
    for (ll i = 2; i*i <= a; i++) {
        if (cp % i == 0) {
            int cnt = 0;
            while (cp % i == 0) {
                cp /= i;
                ++cnt;
            }
            ans = min(ans,calc(i,b)/cnt);
        }
    }
    if (cp > 1) ans = min(ans,calc(cp,b));
    cout << ans << '\n';
}
