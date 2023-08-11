#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll a, b, p, x;
ll mult(ll a, ll b) {
    return (a*b) % p;
}
ll modexp(ll a, ll b) {
    ll res = 1;
    while (b > 0) {
        if (b&1) res = mult(res,a);
        a = mult(a,a);
        b >>= 1;
    }
    return res;
}
ll inverse(ll x) {
    return modexp(x,p-2);
}

const int maxn = 1e6+6;
bool check[maxn];

int main() {
    cin >> a >> b >> p >> x;
    ll ans = 0;
    for (int i = 1; i <= p-1; i++) {
        ll no = mult(b,inverse(modexp(a,i)));
        ll fi = (p-1) * ((i-no+p)%p) + i;
        //cout << i << ": " << no << ' ' << fi << '\n';
        if (fi > x) continue;

        ans += (x-fi) / (p*(p-1)) + 1;
    }
    cout << ans << '\n';
}

