#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll f(ll x) {
    if (x == 1) return 2;
    ll r = 1;
    while (r <= x) {
        r *= 2;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int a = 1; a <= t; a++) {
        ll x; cin >> x;
        ll r = f(x);
        cout << "Pokemon " << a << ": " << (r-x) << '\n';
    }

    return 0;
}

