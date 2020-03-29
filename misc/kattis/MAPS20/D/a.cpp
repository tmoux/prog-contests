#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
ld PI = atan(1)*4;

void solve() {
    int n, l, d, g; cin >> n >> l >> d >> g;
    d *= g;
    ld a = l*l*n/(ld)(4*tan(PI/n));
    a += l*d*n;
    a += PI*d*d;
    cout << fixed << setprecision(10) << a << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}

