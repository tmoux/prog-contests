#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1e9+7;

void solve() {
    int N, K, W; cin >> N >> K >> W;
    vector<ll> L(N), H(N);
    for (int i = 0; i < K; i++) cin >> L[i];
    ll AL, BL, CL, DL; cin >> AL >> BL >> CL >> DL;
    for (int i = 0; i < K; i++) cin >> H[i];
    ll AH, BH, CH, DH; cin >> AH >> BH >> CH >> DH;
    for (int i = K; i < N; i++) {
        L[i] = ((1LL*AL*L[i-2]+1LL*BL*L[i-1]+CL) % DL) + 1;
        H[i] = ((1LL*AH*H[i-2]+1LL*BH*H[i-1]+CH) % DH) + 1;
    }
    ll ans = 1;
    ll perim = 0;
    ll last = 0;
    for (int i = 0; i < N; i++) {
        perim += 2LL*(L[i]+W-max(L[i],last));
        last = L[i]+W;
        ll mx = 0;
        for (int j = i-1; j >= 0; j--) {
            if (L[i] <= L[j]+W) {
                mx = max(mx,H[j]);
            }
            else break;
        }
        //add left and right
        perim += 2LL*max(0LL,H[i]-mx);
        perim %= M;
        ans = (ans*perim) % M;
        //cout << i << ": " << perim << '\n';
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
