#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;
int n, a[maxn];
int pre[maxn];
int m;

int ans[1000006];

int main() {
    cin >> n;
    int mx = 0;
    int sum = 0;
    set<int> s;
    s.insert(0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i-1] + a[i];
        s.insert(pre[i]);
        mx = max(mx,a[i]);
        sum += a[i];
    }
    for (int i = 1; i < mx; i++) {
        ans[i] = -1;
    }
    m = min(sum,mx+800);
    for (int i = mx; i <= m; i++) {
        int cur = 0;
        ans[i] = 1;
        for (int j = 1; j <= n; j++) {
            if (cur+a[j] > i) {
                ans[i]++;
                cur = a[j];
            }
            else {
                cur += a[j];
            }
        }
    }
    int q; cin >> q;
    while (q--) {
        int t; cin >> t;
        if (t <= m) {
            if (ans[t] == -1) cout << "Impossible\n";
            else cout << ans[t] << '\n';
        }
        else {
            int cnt = 1;
            int cur = 0;
            while (s.upper_bound(cur+t) != s.end()) {
                cur = *prev(s.upper_bound(cur+t));
                cnt++;
            }
            cout << cnt << '\n';
        }
    }
}
