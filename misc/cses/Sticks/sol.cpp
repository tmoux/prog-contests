#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 5e5+5;
int n, a[maxn];
ll pfx[maxn];

ll check(int j) {
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res += abs(a[i]-a[j]);                
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a+1,a+n+1);
    a[0] = 2000000000, a[n+1] = 2000000000;
    int lo = 0, hi = n+1;
    while (lo+3<hi) {
        int r1 = lo+(hi-lo)/3;
        int r2 = hi-(hi-lo)/3;
        ll x1 = check(r1);
        ll x2 = check(r2);
        if (x1 >= x2) {
            lo = r1;
        }
        else {
            hi = r2;
        }
        //cout << lo << ' ' << hi << '\n';
    }
    ll res = check(lo);
    for (int i = max(0,lo-50); i <= min(n,lo+50); i++) {
        res = min(res,check(i));
    }
    cout << res << '\n';

    return 0;
}

