#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    int z, w; cin >> z >> w;
    for (int i = 0; i < w; i++) {
        if ((z*i) % w == 0) {
            cout << i << ' ';
        }
    }
    cout << '\n';
    return 0;
    */
    int t; cin >> t;
    while (t--) {
        ll m, d, w; cin >> m >> d >> w;
        ll mn = min(m,d);
        ll D = w/(__gcd(w,(d-1)%w));
        ll l = (mn-1)/D;
        //cout << mn << ' ' << D << ' ' << l << endl;
        ll ans = mn*l;
        ll sub = (l*(l+1)/2)*D;
        ans -= sub;
        cout << ans << '\n';
    }
}
