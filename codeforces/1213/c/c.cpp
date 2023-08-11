#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll getmult(ll x) {
    ll curr = x;
    ll res = 0;
    for (int i = 0; i < 10; i++) {
        res += (curr%10);
        curr += x;
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        ll n, m; cin >> n >> m;
        ll num = n/m;
        ll mult = 0;

        ll ans = (num/10)*getmult(m);
        num %= 10;
        ll curr = m;
        while (num--) {
            ans += (curr%10);
            curr += m;
        }
        cout << ans << '\n';
    }

}

