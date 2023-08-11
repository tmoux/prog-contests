#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    ll ans = 1e18+9;
    for (int i = 0; i < n; i++) {
        ll mx = -1e18-9;
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            for (int k = 0; k < m; k++) {
                mx = max(mx,1LL*a[j]*b[k]);
            }
        }
        ans = min(ans,mx);
    }
    cout << ans << '\n';
}

