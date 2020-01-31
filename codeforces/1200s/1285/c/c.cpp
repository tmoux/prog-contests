#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll expo(ll a, ll b) {
    ll res = 1;
    while (b--) {
        res = res * a;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll x; cin >> x;
    map<ll,int> mp;
    for (ll i = 2; i*i <= x; i++) {
        if (x % i == 0) {
            while (x % i == 0) {
                mp[i]++;
                x /= i;
            }
        }
    }
    if (x > 1) mp[x]++;
    vector<ll> v;
    for (auto p: mp) {
        v.push_back(expo(p.first,p.second));
    }
    int n = v.size();
    pair<ll,ll> ans = {1e18,1e18};
    for (int i = 0; i < (1<<n); i++) {
        ll a = 1, b = 1;
        for (int j = 0; j < n; j++) {
            if (i & (1<<j)) {
                a *= v[j];
            }
            else b *= v[j];
        }
        if (max(a,b) < max(ans.first,ans.second)) {
            ans = {a,b};
        }
    }
    cout << ans.first << ' ' << ans.second << '\n';
}

