#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    int l; cin >> l;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > l && (i == 0 || a[i-1] <= l)) {
            ans++;
        }
    }
    while (m--) {
        int t; cin >> t;
        if (t == 0) {
            cout << ans << '\n';
        }
        else {
            int p, d; cin >> p >> d;
            p--;
            if (a[p] > l) continue;
            a[p] += d;
            if (a[p] > l) {
                bool left = false;
                if (p > 0 && a[p-1] > l) left = true;
                bool right = false;
                if (p < n-1 && a[p+1] > l) right = true;
                if (!left && !right) {
                    ans++;
                }
                else if (left && right) {
                    ans--;
                }
            }
        }
    }
}

