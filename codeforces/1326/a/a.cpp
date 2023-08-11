#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        if (n == 1) {
            cout << -1 << '\n';
        }
        else {
            cout << 2;
            for (int i = 0; i < n-1; i++) {
                cout << 3;
            }
            cout << '\n';
        }
    }
}

