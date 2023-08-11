#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int S(ll x) {
    int r = 0;
    while (x) {
        r += x % 10;
        x /= 10;
    }
    return r;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll n; cin >> n;
    ll x = 0;
    while (10*x+9 <= n) {
        x = 10*x + 9;
    }
    int ans = S(x) + S(n-x);
    //cout << x << ' ' << n-x << '\n';
    cout << ans << '\n';

    return 0;
}

