#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

ll n, m;
int q;

ll part(ll sx, ll sy, ll gc) {
    return sy / (sx/gc);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> q;
    ll gc = __gcd(n,m);
    while (q--) {
        ll sx, sy, ex, ey;
        cin >> sx >> sy >> ex >> ey;
        sy--;
        ey--;
        ll p1 = part(sx==1?n:m,sy,gc);
        ll p2 = part(ex==1?n:m,ey,gc);
        cout << (p1==p2 ? "YES" : "NO") << '\n';
    }
}

