#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll u, v; cin >> u >> v;
    if (u > v || (u+v) % 2 != 0) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> cnt(60,0);
    for (int i = 59; i >= 0; i--) {
        if (u & (1LL<<i)) {
            cnt[i] = 1;
        }
    }
    ll x = v-u;
    for (int i = 0; i < 60; i++) {
        if (x & (1LL<<(i+1))) {
            cnt[i] += 2;
        }
    }
    int ans = 0;
    for (int i = 0; i < 60; i++) {
        ans = max(ans,cnt[i]);
    }
    vector<ll> res; 
    for (int i = 0; i < ans; i++) {
        ll add = 0;
        for (int j = 0; j < 60; j++) {
            if (cnt[j] > 0) {
                add += 1LL<<j;
                cnt[j]--;
            }
        }
        res.push_back(add);
    }
    cout << ans << '\n';
    for (auto j: res) {
        cout << j << ' ';
    }
    cout << '\n';
}
