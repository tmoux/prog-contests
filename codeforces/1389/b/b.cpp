#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, k, z; cin >> n >> k >> z;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int ans = 0;
        for (int i = 0; i <= z; i++) {
            int r = k-2*i;
            int tr = a[0];
            for (int j = 1; j <= r; j++) {
                tr += a[j];
            }
            int mx = 0;
            for (int j = 1; j <= min(n-1,r+1); j++) {
                mx = max(mx,a[j-1]+a[j]);
            }
            tr += i*mx;
            ans = max(ans,tr);
        }
        cout << ans << '\n';
    }
}
