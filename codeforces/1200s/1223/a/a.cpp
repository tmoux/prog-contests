#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int n; cin >> n;
        if (n == 2) {
            cout << 2 << '\n';
        }
        else {
            cout << (n % 2 == 0 ? 0 : 1) << '\n';
        }
    }
}

