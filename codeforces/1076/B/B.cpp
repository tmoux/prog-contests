#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll fac(ll x) {
    for (ll j = 2; j*j <= x; j++) {
        if (x % j == 0) return j;
    }
    return x;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    if (n % 2 == 0) {
        cout << n/2 << '\n';
    }
    else {
        ll f = fac(n);
        cout << 1 + (n-f)/2 << '\n';
    }

    return 0;
}

