#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        deque<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        deque<int> w(k);
        for (int i = 0; i < k; i++) {
            cin >> w[i];
        }
        sort(a.begin(),a.end());
        sort(w.begin(),w.end());
        ll ans = 0;
        while (!w.empty() && w.front() == 1) {
            ans += 2*a.back(); a.pop_back();
            w.pop_front();
        }
        while (!w.empty()) {
            int W = w.back(); w.pop_back();
            ans += a.back(); a.pop_back();
            if (W > 1) {
                ans += a.front(); a.pop_front();
                for (int i = 0; i < W-2; i++) {
                    a.pop_front();
                }
            }
        }
        cout << ans << '\n';
    }
}
