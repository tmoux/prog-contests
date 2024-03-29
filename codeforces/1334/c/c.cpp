#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<pair<ll,ll>> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i].first >> v[i].second;
        }
        ll ans = 0, mn = 1e18;
        for (int i = 0; i < n; i++) {
            int next = (i+1)%n;
            ll val = min(v[next].first,v[i].second);
            ans += v[next].first-val;
            mn = min(mn,val);
        }
        ans += mn;
        cout << ans << '\n';
    }
}

