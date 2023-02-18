#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int rem(ll x) {
    return x % 9 == 0 ? 9 : x % 9;
}

ll sum(ll x) {
    if (x == 0) return 0;
    ll res = 0;
    while (x % 9 != 0) {
        res += rem(x);
        x--;
    }
    res += 45LL*(x/9);
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        ll l, r; cin >> l >> r;
        cout << (sum(r)-sum(l-1)) << '\n';
    }
}
