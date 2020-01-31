#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll X0, Y0, ax, ay, bx, by, xs, ys, t;
const ll mx = 1e16+50000;

ll dist(pair<ll,ll> a, pair<ll,ll> b) {
    return abs(a.first-b.first) + abs(a.second-b.second);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> X0 >> Y0 >> ax >> ay >> bx >> by >> xs >> ys >> t;
    vector<pair<ll,ll>> v;
    v.push_back({X0,Y0});
    while (true) {
        ll x = ax*v.back().first+bx;
        ll y = ay*v.back().second+by;
        v.push_back({x,y});
        if (max(x,y) >= mx) break;
    }
    int ans = 0;
    /*
    for (auto p: v) {
        cout << p.first << ' ' << p.second << '\n';
    }
    */
    for (int i = 0; i < v.size(); i++) {
        for (int j = i; j < v.size(); j++) {
            ll tr = dist(v[i],v[j]) + min(dist({xs,ys},v[i]),dist({xs,ys},v[j]));
            if (tr <= t) {
                ans = max(ans,j-i+1);
            }
        }
    }
    cout << ans << '\n';
}

