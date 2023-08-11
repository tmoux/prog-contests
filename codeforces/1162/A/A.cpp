#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, h, m; cin >> n >> h >> m;
    vector<int> a(n+1,h);
    for (int i = 0; i < m; i++) {
        int l, r, x; cin >> l >> r >> x;
        for (int j = l; j <= r; j++) {
            a[j] = min(a[j],x);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += a[i]*a[i];
    }
    cout << ans << '\n';
}

