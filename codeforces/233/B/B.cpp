#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n;
ll s(ll x) {
    ll r = 0;
    while (x) {
        r += x % 10;
        x /= 10;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    ll root = max(1LL,(ll)((-81+sqrt(81*81+4*n))/2)-50);
    //cout << root << '\n';
    for (ll i = root; i <= root + 250; i++) {
        if (i*i+i*s(i) == n) {
            cout << i << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';

    return 0;
}

