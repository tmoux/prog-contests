#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 3e5+5;
int n, m;
ll k;
ll a[maxn];
ll mod[10];
ll pre[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
        //cout << i << ": " << pre[i] << '\n';
    }
    for (int i = 0; i < m; i++) {
        mod[i] = -1LL<<62;
    }

    ll ans = 0;
    for (int i = n, d = 0; i >= 1; i--, d++) {
        ll level = d/m;
        mod[d%m] = max(mod[d%m],pre[i]+k*level);
        ll tr = 0;
        for (int j = 0; j < m; j++) {
            ll dist = (n-j) - i + 1;
            if (dist <= 0) continue;
            ll tt = mod[j]-(ll)k*(ll)ceil((dist*1.0)/m) - pre[i-1];
            //cout << i << ' ' << j << ' ' << dist << ": " << tt << '\n';
            //cout << mod[j] << '\n';
            tr = max(tr,tt);
        }
        ans = max(ans,tr);
    }
    cout << ans << '\n';
}
