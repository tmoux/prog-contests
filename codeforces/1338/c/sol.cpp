#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll solve(ll n) {
    --n;
    ll index = n/3;
    ll off = 1;
    for (;index-off >= 0; off <<= 2) {
        index -= off;
    }
    ll fi = index + off;
    //determine 2nd number
    ll se = off<<1;
    /*
    cout << "fi = " << fi << '\n';
    cout << "se = " << se << '\n';
    cout << "idx = " << index << endl;
    cout << "off = " << off << '\n';
    */
    for (ll place = off>>2; place >= 1; place >>= 2) {
        ll t = (index/place) % 4;
        if (t == 0) {
            se += 0*place;
        }
        else if (t == 1) {
            se += 2*place;
        }
        else if (t == 2) {
            se += 3*place;
        }
        else if (t == 3) {
            se += 1*place;
        }
    }
    ll th = fi^se;
    if (n % 3 == 0) return fi;
    else if (n % 3 == 1) return se;
    else return th;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    /*
    int n; cin >> n;
    for (int i = 1; i <= 3*n;) {
        for (int j = 0; j < 3; j++, i++) {
            cout << solve(i) << ' ';
        }
        cout << '\n';
    }
    return 0;
    */
    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        cout << solve(n) << '\n';
    }
}

