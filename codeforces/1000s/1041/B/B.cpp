#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll a, b, x, y; cin >> a >> b >> x >> y;
    ll gc = __gcd(x,y);
    x /= gc; y /= gc;
    ll ans = min(a/x,b/y);
    cout << ans << '\n';

    return 0;
}

