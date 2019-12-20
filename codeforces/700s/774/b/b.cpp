#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m, d;

pair<int,int> a[maxn], b[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> d;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i].first >> b[i].second;
    }
    sort(a,a+n,[](auto a, auto b) {
        return a.first != b.first ? 
            a.first > b.first:
            a.second < b.second;
            });

    sort(b,b+m,[](auto a, auto b) {
        return a.first != b.first ? 
            a.first > b.first:
            a.second < b.second;
            });

    ll total_width = 0, total_sig = 0;
    vector<pair<ll,ll>> a1;
    for (int i = 0; i < n; i++) {
        total_sig += a[i].first;
        total_width += a[i].second;
        a1.push_back({total_width,total_sig});
    }
    total_width = 0;
    total_sig = 0;
    vector<pair<ll,ll>> b1;
    for (int i = 0; i < m; i++) {
        total_sig += b[i].first;
        total_width += b[i].second;
        b1.push_back({total_width,total_sig});
    }
    ll ans = 0;
    for (auto p: a1) {
        ll d1 = p.first;
        if (d-d1 <= 0) break;
        pair<ll,ll> f = {d-d1,1LL<<60};
        auto it = upper_bound(b1.begin(),b1.end(),f);
        if (it != b1.begin()) {
            --it;
            ans = max(ans,p.second+it->second);
        }
    }
    cout << ans << '\n';
}
