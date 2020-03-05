#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, d; cin >> n >> d;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = a[0];
        for (int i = 1; i < n; i++) {
            while (d >= i && a[i] > 0) {
                a[i]--;
                d -= i;
                ans++;
            }
        }
        cout << ans << endl;
    }
}

