#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n, p, d, w; cin >> n >> p >> w >> d;
    ll gc = __gcd(w,d);
    if (p % gc == 0) {
        w /= gc;
        d /= gc;
        p /= gc;
        
        for (ll i = 0; i <= 100000; i++) {
            ll y = i;
            if ((p - y*d) % w == 0) {
                ll x = (p-y*d)/w;
                ll z = n - x - y;
                if (0 <= x && 0 <= y && 0 <= z) {
                    assert(w*x + d*y == p);
                    cout << x << ' ' << y << ' ' << z << '\n';
                    return 0;
                }
            }
        }
    }
    cout << -1 << '\n';
}

