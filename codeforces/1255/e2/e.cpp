#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6+6;
const ll INF = 1e18;
int n, a[maxn];
ll pre[maxn];
ll tot = 0;

ll check(ll x) {
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res += min(pre[i]%x,x-(pre[i]%x));
    }
    //cout << x << ": " << res << '\n';
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
        pre[i] = pre[i-1] + a[i];
    }
    if (tot == 1) {
        cout << -1 << '\n';
        return 0;
    }
    ll ans = INF;
    for (ll i = 2; i*i <= tot; i++) {
        if (tot % i == 0) {
            ans = min(ans,check(i));
            while (tot%i==0) {
                tot /= i;
            }
        }
    }
    if (tot > 1) ans = min(ans,check(tot));
    cout << ans << '\n';
}

