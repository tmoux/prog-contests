#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int maxn = 1e5+5;
ld modexp(ld a, int p) {
    ld res = 1.0;
    while (p) {
        if (p&1) res *= a;
        a = a*a;
        p >>= 1;
    }
    return res;
}
ld p[maxn], q[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    for (int i = 1; i <= m; i++) {
        p[i] = modexp((ld)(i)/m,n);
        q[i] = p[i] - p[i-1];
    }
    ld ans = 0.0;
    for (int i = 1; i <= m; i++) {
        ans += q[i]*i;
    }
    cout << fixed << setprecision(10) << ans << '\n';
}

