#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;
int b[maxn], g[maxn];
int cnt[maxn];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        ans += 1LL*b[i]*m;
    }
    for (int i = 0; i < m; i++) {
        cin >> g[i];
    }
    sort(b,b+n);
    sort(g,g+m);
    if (g[0] < b[n-1]) {
        cout << -1 << '\n';
        return 0;
    }
    int pt = n-1;
    for (int i = m-1; i >= 0; i--) {
        while (pt >= 0 && b[pt] > g[i]) {
            pt--;
        }
        if (cnt[pt] == m-1 && g[i] > b[pt]) pt--;
        if (pt < 0) {
            cout << -1 << '\n';
            return 0;
        }
        ans += g[i]-b[pt];
        if (g[i] > b[pt]) {
            cnt[pt]++;
        }
        //cout << i << ": " << ans << endl;
    }
    cout << ans << endl;
}
