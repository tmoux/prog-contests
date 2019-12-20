#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        for (int i = 0; i < n-1; i++) {
            int x, y; cin >> x >> y;
        }
        cout << (n&1?"Alice":"Bob") << '\n';
    }
}

