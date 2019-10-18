#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll x, y; cin >> x >> y;
        ll diff = x - y;
        if (diff == 1) {
            cout << "NO\n";
        }
        else {
            cout << "YES\n";
        }
    }
}

