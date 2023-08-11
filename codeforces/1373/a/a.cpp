#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll a, b, c; cin >> a >> b >> c;
        if (a >= c) {
            cout << -1 << ' ' << b << '\n';
        }
        else {
            if (a*b <= c) {
                cout << 1 << ' ' << -1 << '\n';
            }
            else {
                cout << 1 << ' ' << b << '\n';
            }
        }
    }
}
