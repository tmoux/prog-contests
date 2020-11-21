#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<int> a(n);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i > 0 && a[i] > a[i-1]) cnt++;
        }
        if (k == 1) {
            cout << (cnt == 0 ? 1 : -1) << '\n';
        }
        else {
            cout << max(1,(cnt+k-2)/(k-1)) << '\n';
        }
    }
}
