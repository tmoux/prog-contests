#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n, a, b, p, q; cin >> n >> a >> b >> p >> q;
    ll lc = a*b/__gcd(a,b);
    ll ans = 0;
    ans += p*(n/a-n/lc);
    ans += q*(n/b-n/lc);
    ans += max(p,q)*(n/lc);
    cout << ans << '\n';
}

