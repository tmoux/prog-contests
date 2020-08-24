#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a0, a1, a2, b0, b1, b2;
        cin >> a0 >> a1 >> a2 >> b0 >> b1 >> b2;
        int pos = min(a2,b1);
        int ans = 2*pos;
        b1 -= pos;
        a1 -= min(a1,b0);
        a1 -= min(a1,b1);
        ans -= 2*a1;
        cout << ans << '\n';
    }
}
