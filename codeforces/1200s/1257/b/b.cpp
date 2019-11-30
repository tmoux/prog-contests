#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int x, y; cin >> x >> y;
        if (x >= 4) {
            cout << "YES\n";
        }
        else {
            if (x == 1 && y == 1) {
                cout << "YES\n";
            }
            else if (x > 1 && y < 4) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
}

