#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        int ans = 0;
        while (c >= 2 && b >= 1) {
            c -= 2;
            b -= 1;
            ans += 3;
        }
        while (b >= 2 && a >= 1) {
            b -= 2;
            a -= 1;
            ans += 3;
        }
        cout << ans << '\n';
    }
}

