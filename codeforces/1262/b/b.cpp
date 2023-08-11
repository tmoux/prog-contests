#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> q(n), ans(n);
        set<int> s;
        for (int i = 1; i <= n; i++) {
            s.insert(i);
        }
        for (int i = 0; i < n; i++) {
            cin >> q[i];
            if (i == 0 || q[i] > q[i-1]) {
                ans[i] = q[i];
                s.erase(q[i]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (ans[i] == 0) {
                ans[i] = *s.begin();
                s.erase(s.begin());
            }
        }
        int mx = 0;
        bool poss = true;
        for (int i = 0; i < n; i++)  {
            mx = max(mx,ans[i]);
            if (mx != q[i]) {
                poss = false;
                break;
            }
        }
        if (poss) {
            for (int i = 0; i < n; i++) {
                cout << ans[i] << ' ';
            }
            cout << '\n';
        }
        else {
            cout << -1 << '\n';
        }
    }
}

