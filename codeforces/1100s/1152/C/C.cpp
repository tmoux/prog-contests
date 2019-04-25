#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) {
    if (a == 0 || b == 0) return a + b;
    return gcd(b,a%b);
}

ll lcm(ll a, ll b) {
    return a*b/gcd(a,b);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b; cin >> a >> b;
    if (a > b) swap(a,b);
    if (a == b) {
        cout << 0 << '\n';
        return 0;
    }
    ll diff = b-a;
    ll k = 0;
    ll bestans = lcm(a,b);
    for (ll i = 1; i*i <= diff; i++) {
        if (diff % i == 0) {
            ll d1 = i;
            ll d2 = diff/i;
            ll x1 = d1 - (a % d1);
            ll x2 = d2 - (a % d2);    
            ll l1 = lcm(a+x1,b+x1);
            ll l2 = lcm(a+x2,b+x2);
            /*
            cout << x1 << ": " << l1 << '\n';
            cout << x2 << ": " << l2 << '\n';
            */

            if (l1 < bestans) {
                bestans = l1;
                k = x1;
            }
            else if (l1 == bestans) k = min(k,x1);

            if (l2 < bestans) {
                bestans = l2;
                k = x2;
            }
            else if (l2 == bestans) k = min(k,x2);
        }
    }
    cout << k << '\n';


    return 0;
}

