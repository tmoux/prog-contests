#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int b[maxn], p[maxn], n, m;
ll a;

ll need(int r) {
    ll excess = 0;
    for (int i = 1; i <= r; i++) {
        int j = n-r+i;
        excess += max(p[i]-b[j],0);
        //cout << p[i] << ' ' << b[j] << '\n';
    }
    return excess;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> a;
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= m; i++) cin >> p[i];
    sort(b+1,b+n+1);
    sort(p+1,p+m+1);
    int lo = 0, hi = min(n,m)+1;
    if (need(1) > a) {
        cout << "0 0\n";
        return 0;
    }
    while (lo + 1 < hi) {
        int m = (lo+hi)/2;
        bool is = need(m) <= a;
        if (is) lo = m;
        else hi = m;
    }
    int r = lo;
    int s = need(r);
    ll total = 0;
    for (int i = 1; i <= r; i++) total += p[i];
    ll personal = total - s;
    personal -= (a-s);
    cout << r << ' ' << max(0LL,personal) << '\n';

    return 0;
}

