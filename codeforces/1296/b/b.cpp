#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int s; cin >> s;
        ll ans = 0;
        while (s >= 10) {
            ll add = (s/10)*10;
            s -= add;
            s += add/10;
            ans += add;
        }
        ans += s;
        cout << ans << endl;
    }
}

