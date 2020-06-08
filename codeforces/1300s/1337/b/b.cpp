#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int x, n, m; cin >> x >> n >> m;
        for (int i = 0; i < n; i++) {
            int nx = x/2+10;
            x = min(x,nx);
            if (x <= 0) break;
        }
        x -= m*10;
        cout << (x<=0?"YES":"NO") << '\n';
    }
}
