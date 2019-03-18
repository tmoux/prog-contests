#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll fsum(ll n, ll p, ll q) {
    int t = __gcd(p,q);
    p /= t;
    q /= t;
    ll s = 0;
    ll z = 1;
    while (q > 0 && n > 0) {
        t = p/q;
        s += z*t*n*(n+1)/2;
        p = p - q*t;
        t = n/q;
        s += z*p*t*(n+1) - z*t*(p*q*t + p + q - 1)/2;
        n = n - q*t;
        t = (n*p)/q;
        s += z*t*n;
        n = t;
        swap(p,q);
        z = -z;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        ll n, p, q; cin >> p >> q >> n;
        ll a = p*(n+1)*(n)/2;
        ll b = q*fsum(n,p,q);
        cout << (a-b) << '\n';
    }
}
