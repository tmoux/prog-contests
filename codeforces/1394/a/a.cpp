#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, d, m; cin >> n >> d >> m;
    vector<int> a(n+1,0);
    vector<ll> pre(n+1,0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    for (int i = 1; i <= n; i++) {
        pre[i] = a[i] + pre[i-1];
    }
    int idx = 0;
    while (idx + 1 <= n && a[idx+1] <= m) idx++;
    if (idx == n) {
        cout << pre[n] << '\n';
        return 0;
    }
    ll ans = 0;
    int nbig = 0;
    ll cur = 0;
    for (int i = n; i >= 1 && a[i] > m; i--) {
        cur += a[i];
        nbig++;
        ll nsmall = max(0LL,1LL*(nbig-1)*d);
        if (nsmall + nbig <= n) {
            int nleft = n - nsmall - nbig;
            ll tr = cur + (pre[idx] - pre[max(0,idx-nleft)]);
            ans = max(ans,tr);
        }
    }
    cout << ans << '\n';
}
