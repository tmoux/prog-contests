#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a,ll b) {
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
    ll k = 0;
    ll bestans = lcm(a,b);
    for (int i = 0; i < 1000000; i++) {
        ll x = lcm(a+i,b+i);
        if (x < bestans) {
            bestans = x;
            k = i;
        }
    }
    cout << k << '\n';


    return 0;
}

