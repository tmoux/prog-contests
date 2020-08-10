#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll a, b; cin >> a >> b;
        int ca = 0, cb = 0;
        while (a % 2 == 0) {
            a /= 2;
            ca++;
        }
        while (b % 2 == 0) {
            b /= 2;
            cb++;
        }
        if (a != b) {
            cout << -1 << '\n';
        }
        else {
            int diff = abs(ca-cb);
            cout << ((diff+2)/3) << '\n';
        }
    }
}
