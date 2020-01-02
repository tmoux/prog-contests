#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n;
ll m;
ll a[maxn];
ll pre[maxn];

ll cnt(ll x) {
    ll res = 0;
    int pt = 0;
    for (int i = n-1; i >= 0; i--) {
        while (pt < n && a[pt]+a[i] >= x) pt++;
        res += pt;
    }
    //cout << x << ": " << res << endl;
    return res;
}

ll get(ll x) {
    ll res = 0;
    int pt = 0;
    for (int i = n-1; i >= 0; i--) {
        while (pt < n && a[pt]+a[i] >= x) pt++;
        res += pre[pt-1]+pt*a[i];
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a,a+n,greater<ll>());
    for (int i = 0; i < n; i++) {
        pre[i] = i==0?a[i]:a[i]+pre[i-1];
    }
    ll lo = 0, hi = 1e16;
    //find maximum x s.t. cnt(x) >= n
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        if (cnt(mid) >= m) {
            lo = mid;
        }
        else hi = mid;
    }
    cout << get(lo)-(cnt(lo)-m)*lo << '\n';
}

