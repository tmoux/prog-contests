#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll a, b, x, y, n; cin >> a >> b >> x >> y >> n;
        auto calc = [](ll a, ll b, ll x, ll y, ll n) {
            ll mn = min(a-x,n);
            n -= mn;
            a -= mn;
            mn = min(b-y,n);
            b -= mn;
            return a*b;
        };
        ll ans = calc(a,b,x,y,n);
        ans = min(ans,calc(b,a,y,x,n));
        cout << ans << '\n';
    }
}
