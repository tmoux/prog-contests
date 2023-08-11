#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int l, r; cin >> l >> r;
        if (2*l <= r) {
            cout << l << ' ' << (2*l) << '\n';
        }
        else {
            cout << -1 << ' ' << -1 << '\n';
        }
    }
}
