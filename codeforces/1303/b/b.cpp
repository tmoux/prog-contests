#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll t; cin >> t;
    while (t--) {
        ll n, b, g; cin >> n >> g >> b;
        ll need = n&1 ? n/2+1 : n/2;
        ll quo = need/g;
        if (need % g != 0) {
            ll ans = quo*(b+g)+(need%g);
            cout << max(ans,n) << '\n';
        }
        else {
            ll ans = (quo-1)*(b+g) + g;
            cout << max(ans,n) << '\n';
        }
    }
}

