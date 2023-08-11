#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll ans = 0;
        for (int i = n-1; i >= 0; i--) {
            if (i-1 >= 0 && a[i] < a[i-1]) {
                ans += a[i-1] - a[i];
            }
        }
        cout << ans << '\n';
    }
}
