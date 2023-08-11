#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll gcd(ll a, ll b) {
    return a==0?b:gcd(b%a,a);
}

bool solve() {
    ll p, q, b; cin >> p >> q >> b;
    if (p == 0) return true;
    ll gc = gcd(p,q);
    p /= gc;
    q /= gc;
    ll x;
    while ((x = gcd(q,b)) > 1) {
        while (q % x == 0) q /= x;    
        x = gcd(q,b);
    }
    return q == 1;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        bool is = solve();
        cout << (is?"Finite":"Infinite") << '\n';
    }
    

    return 0;
}

