#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m; //n = # events, m = settings for interval

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    vector<ll> x(n);
    ll gc = 0;
    ll mn = 2e18;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        mn = min(mn,x[i]);
        if (i > 0) {
            if (gc == 0) gc = x[i] - x[i-1];
            else gc = __gcd(gc,x[i]-x[i-1]);
        }
    }
    vector<ll> p(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i];
    }
    if (n == 1) {
        cout << "YES\n";
        cout << mn << ' ' << 1 << '\n';
        return 0;
    }
    else {
        for (int i = 0; i < m; i++) {
            if (gc % p[i] == 0) {
                cout << "YES\n";
                cout << mn << ' ' << (i+1) << '\n';
                return 0;
            }
        }
        cout << "NO\n";
    }
}

