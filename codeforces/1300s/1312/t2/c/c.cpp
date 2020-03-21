#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<ll> a(n);
        ll mx = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx,a[i]);
        }
        ll d = k;
        while (d <= mx) d *= k;
        bool poss = true;
        while (d > 0) {
            int cnt = 0;
            for (int i = 0; i < n; i++) {
                while (a[i] >= d) {
                    a[i] -= d;
                    cnt++;
                }
            }
            if (cnt > 1) {
                poss = false;
                break;
            }
            d /= k;
        }
        cout << (poss ? "YeS" : "No") << endl;
    }
}
