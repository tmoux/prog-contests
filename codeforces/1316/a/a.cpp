#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int ai; cin >> ai;
            if (i == 0) ans = ai;
            else {
                int mn = min(m-ans,ai);
                ans += mn;
            }
        }
        cout << ans << endl;
    }
}

