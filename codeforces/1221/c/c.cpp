#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int q; cin >> q;
    while (q--) {
        int c, m, x; cin >> c >> m >> x;
        int d = min(c,m);
        c -= d;
        m -= d;
        int t = c + m + x;
        if (d > t) {
            int diff = d-t;
            d -= diff/3;
            t += 2*diff/3;
        }
        //cout << d << ' ' << t << '\n';
        int ans = min(d,t);
        cout << ans << '\n';
    }
}

