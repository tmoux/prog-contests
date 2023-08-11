#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<ll> diffs;
        ll mx = -2e9;
        for (int i = 0; i < n; i++) {
            diffs.push_back(max(0LL,mx-a[i]));
            mx = max(mx,a[i]);
        }
        int ans = 0;
        for (auto i: diffs) {
            if (i) ans = max(ans,64-__builtin_clzll(i));
        }
        cout << ans << '\n';
    }
}

