#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;

void solve() {
    int N, M, K;
    ll S; 
    cin >> N >> M >> K >> S;
    vector<ll> P(N), Q(M);
    for (int i = 0; i < K; i++) cin >> P[i];
    ll AP, BP, CP, DP; cin >> AP >> BP >> CP >> DP;
    for (int i = 0; i < K; i++) cin >> Q[i];
    ll AQ, BQ, CQ, DQ; cin >> AQ >> BQ >> CQ >> DQ;
    for (int i = K; i < N; i++) {
        P[i] = ((AP*P[i-2]+BP*P[i-1]+CP) % DP) + 1;
    }
    for (int i = K; i < M; i++) {
        Q[i] = ((AQ*Q[i-2]+BQ*Q[i-1]+CQ) % DQ) + 1;
    }
    sort(P.begin(),P.end());
    sort(Q.begin(),Q.end());
    auto check = [&N,&M,&S,&P,&Q](ll x) {
        int l = 0, r = 0;
        for (int i = 0; i < N; i++) {
            while (r < M && Q[r] < P[i]) r++;
            ll cur = x;
            ll left_path = 0;
            if (r > l) {
                left_path = P[i]-Q[l];
                cur -= left_path;
                if (cur < 0) return false;
                while (r > l) {
                    if (cur-S >= 0) {
                        cur -= S;
                        l++;
                    }
                    else break;
                }
            }
            if (l >= r) {
                while (l < M) {
                    ll right_path = Q[l]-P[i];    
                    if (cur-S-right_path-min(left_path,right_path) >= 0) {
                        cur -= S;
                        l++;
                    }
                    else break;
                }
            }
        }
        return l == M;
    };
    ll lo = 0, hi = 1e18;    
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        if (check(mid)) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    ll ans = hi;
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
