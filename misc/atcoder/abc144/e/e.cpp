#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n;
ll k;
ll a[maxn], f[maxn];

ll ceil(ll a, ll b) {
    return (a+b-1)/b;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    sort(a,a+n);
    sort(f,f+n,greater<ll>());
    ll lo = -1, hi = 1e18+5;
    while (lo + 1 < hi) {
        ll mid = (lo+hi)/2;
        ll s = 0;
        for (int i = 0; i < n; i++) {
            ll need = max(0LL,ceil(a[i]*f[i]-mid,f[i]));
            s += need;
            assert((a[i]-need)*f[i] <= mid);
        }
        //cout << mid << ": " << s << '\n';
        if (s <= k) {
            hi = mid;
        }
        else {
            lo = mid;
        }
    }
    cout << hi << '\n';
}

