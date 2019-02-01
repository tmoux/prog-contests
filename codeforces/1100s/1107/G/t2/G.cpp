#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, a, val[maxn], dist[maxn];

ll maxSubarray(int l, int r) {
    if (l > r) return -(1LL<<62);
    if (l == r) return val[l];
    int m = (l+r)/2;
    ll maxrsum = val[m];
    ll rsum = val[m];
    for (int rp = m + 1; rp <= r; r++) {
        rsum += val[rp];
        maxrsum = max(maxrsum,rsum);
    }
    ll maxlsum = 0;
    ll lsum = 0;
    for (int lp = m-1; lp >= l; lp--) {
        lsum += val[lp];
        maxlsum = max(maxlsum,lsum);
    }
    ll res = maxrsum + maxlsum;
    
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> a;
    for (int i = 1; i <= n; i++) {
        cin >> dist[i] >> val[i];
        val[i] = a - val[i];
    }
    


    return 0;
}

