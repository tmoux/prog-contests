#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < 2 && k > 0; i++,k--) {
            int mx = -2e9;
            for (int i = 0; i < n; i++) {
                mx = max(mx,a[i]);
            }
            for (int i = 0; i < n; i++) {
                a[i] = mx-a[i];
            }
        }
        if (k % 2 == 1) {
            int mx = -2e9;
            for (int i = 0; i < n; i++) {
                mx = max(mx,a[i]);
            }
            for (int i = 0; i < n; i++) {
                a[i] = mx-a[i];
            }
        }
        for (int i = 0; i < n; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
    }
}
