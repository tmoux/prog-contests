#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll u, v; cin >> u >> v;
    if (u > v || (u+v) % 2 == 1) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> cnt(60,0);
    for (int i = 0; i < 60; i++) {
        if (u & (1LL<<i)) ++cnt[i];
    }
    ll x = (v-u)>>1;
    for (int i = 0; i < 60; i++) {
        if (x & (1LL<<i)) cnt[i] += 2;
    }
    vector<ll> vec;
    for (int i = 0; i < 3; i++) {
        ll add = 0;
        for (int j = 0; j < 60; j++) {
            if (cnt[j] > 0) {
                add |= (1LL<<j);
                --cnt[j];
            }
        }
        if (add > 0) vec.push_back(add);
    }
    cout << vec.size() << '\n';
    for (auto i: vec) {
        cout << i << ' ';
    }
    cout << '\n';
}

