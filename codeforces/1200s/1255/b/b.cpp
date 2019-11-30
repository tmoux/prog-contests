#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<int> a(n+1);
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            sum += 2*a[i];
        }
        if (m < n || n <= 2) {
            cout << -1 << '\n';
        }
        else {
            cout << sum << '\n';
            for (int i = 1; i < n; i++) {
                cout << i << ' ' << i+1 << '\n';
            }
            cout << n << ' ' << 1 << '\n';
        }
    }
}

