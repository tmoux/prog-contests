#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        ll p, f; cin >> p >> f;
        ll cnt_s, cnt_w; cin >> cnt_s >> cnt_w;
        ll s, w; cin >> s >> w;
        ll ans = 0;
        for (ll i = 0; i <= cnt_s; i++) {
            ll tr = i;
            ll np = p-s*i;
            if (np < 0) continue;
            ll take_w = min(np/w,cnt_w);
            tr += take_w;

            ll left_s = cnt_s - i;
            ll left_w = cnt_w - take_w;

            ll nf = f;
            if (s < w) {
                ll f_take_s = min(left_s,nf/s);
                tr += f_take_s;
                nf -= f_take_s*s;

                ll f_take_w = min(left_w,nf/w);
                tr += f_take_w;
                nf -= f_take_w*w;
            }
            else {
                ll f_take_w = min(left_w,nf/w);
                tr += f_take_w;
                nf -= f_take_w*w;

                ll f_take_s = min(left_s,nf/s);
                tr += f_take_s;
                nf -= f_take_s*s;
            }
            ans = max(ans,tr);
        }
        cout << ans << '\n';
    }
}
