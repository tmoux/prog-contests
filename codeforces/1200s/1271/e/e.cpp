#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, k;

ll cnt(ll x) {
    ll res = 0;
    ll orig = x;
    for (int i = 0; x <= n; x *= 2, i++) {
        res += min(n,x+(1LL<<i)-1) - x + 1;
    }
    if (orig % 2 == 0) res += cnt(orig+1);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    int digits = 0;
    ll cp = n;
    while (cp > 0) {
        digits++;
        cp >>= 1;
    }
    ll odd_ans = 0;
    for (int d = digits-1; d >= 1; d--) {
        ll lo = 1LL<<(d-1);
        ll hi = 1LL<<d;
        if (cnt((lo<<1)|1) < k) {
            //no hope, break out
            continue;
        }
        else {
            while (lo + 1 < hi) {
                ll mid = (lo+hi)/2;
                ll x = (mid<<1)|1;
                //cout << x << ": " << cnt(x) << '\n';
                if (cnt(x) >= k) {
                    lo = mid;
                }
                else hi = mid;
            }
            odd_ans = (lo<<1)|1;
            break;
        }
    }
    if (odd_ans == 0) odd_ans = 1;

    ll even_ans = 0;
    for (int d = digits-1; d >= 1; d--) {
        ll lo = 1LL<<(d-1);
        ll hi = 1LL<<d;
        //cout << d << ": " << (cnt(lo<<1)) << '\n';
        if (cnt(lo<<1) < k) {
            //no hope, continue on
            continue;
        }
        else {
            while (lo + 1 < hi) {
                ll mid = (lo+hi)/2;
                ll x = mid<<1;
                //cout << x << ": " << cnt(x) << '\n';
                if (cnt(x) >= k) {
                    lo = mid;
                }
                else hi = mid;
            }
            even_ans = lo<<1;
            break;
        }
    }
    cout << max(odd_ans,even_ans) << '\n';
}

