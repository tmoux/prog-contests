#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
typedef long long ll;

ll l, r, x, y;

ll gcd(ll a, ll b) {
    while (b) {
        ll t = a%b;
        a = b;
        b = t;
    }
    return a;
}

int main()
{
    //ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> l >> r >> x >> y;
    if (y % x != 0) {
        cout << 0 << '\n';
        return 0;
    }
    else {
        ll ans = 0;
        ll n = y / x;
        for (ll d = 1; d * d <= n; ++d) {
            if (n % d == 0) {
                ll c = n / d;
                if (l <= c * x && c * x <= r && l <= d * x && d * x <= r && gcd(c,d) == 1) {
                    if (d*d == n) ans++;
                    else {
                        ans += 2;
                    }
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
	

