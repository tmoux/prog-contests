#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7, INF = 2e9;

ll norm(ll x) {
    while (x < 0) x += M;
    x %= M;
    return x;
}

void solve() {
    int N, K; cin >> N >> K;
    vector<ll> L(N), W(N), H(N);
    for (int i = 0; i < K; i++) cin >> L[i];
    ll AL, BL, CL, DL; cin >> AL >> BL >> CL >> DL;
    for (int i = 0; i < K; i++) cin >> W[i];
    ll AW, BW, CW, DW; cin >> AW >> BW >> CW >> DW;
    for (int i = 0; i < K; i++) cin >> H[i];
    int AH, BH, CH, DH; cin >> AH >> BH >> CH >> DH;
    for (int i = K; i < N; i++) {
        L[i] = ((1LL*AL*L[i-2]+1LL*BL*L[i-1]+CL) % DL) + 1;
        W[i] = ((1LL*AW*W[i-2]+1LL*BW*W[i-1]+CW) % DW) + 1;
        H[i] = ((1LL*AH*H[i-2]+1LL*BH*H[i-1]+CH) % DH) + 1;
    }
    ll ans = 1;
    ll perim = 0;
    set<pair<ll,ll>> segs;
    for (int i = 0; i < N; i++) {
        pair<ll,ll> p = {L[i],0};
        auto it = segs.lower_bound(p);
        if (it != segs.begin() && prev(it)->second >= p.first) --it;
        p = {L[i]+W[i],0};        
        auto it2 = segs.upper_bound(p);
        ll l = L[i], r = L[i]+W[i];
        perim += 2LL*H[i];
        perim = norm(perim);
        for (; it != it2;) {
            perim -= 2LL*(it->second-it->first);
            perim = norm(perim);
            perim -= 2LL*H[i];
            perim = norm(perim);
            l = min(l,it->first);
            r = max(r,it->second);
            it = segs.erase(it);
        }

        segs.insert({l,r});
        perim += 2LL*(r-l);
        perim = norm(perim);

        ans = (ans*perim) % M;
        /*
        for (auto p: segs) {
            cout << p.first << ' ' << p.second << '\n';
        }
        cout << i << " perim : " << perim << '\n';
        */
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";
        solve();
    }
}
