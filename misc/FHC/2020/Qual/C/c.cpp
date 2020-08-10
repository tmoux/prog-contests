#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void amax(ll& a, ll b) {
    a = max(a,b);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int iter = 1; iter <= t; iter++) {
        cout << "Case #" << iter << ": ";
        int n; cin >> n;
        vector<pair<ll,ll>> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        sort(a.begin(),a.end());
        map<ll,ll> rs, ls;
        for (auto p: a) {
            amax(rs[p.first+p.second],rs[p.first]+p.second);
        }
        reverse(a.begin(),a.end());
        for (auto p: a) {
            amax(ls[p.first-p.second],ls[p.first]+p.second);
        }
        ll ans = 0;
        for (auto p: rs) {
            amax(ans,rs[p.first]+ls[p.first]);
        }
        for (auto p: ls) {
            amax(ans,rs[p.first]+ls[p.first]);
        }
        cout << ans << '\n';
    }
}
