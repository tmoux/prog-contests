#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        vector<int> d(n);
        for (int i = 0; i < n; i++) {
            d[i] = s[i]-'0';
        }
        int ans = n;
        for (int i = 0; i <= 9; i++) {
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (d[j] == i) cnt++;
            }
            ans = min(ans,n-cnt);
        }
        for (int d1 = 0; d1 <= 9; d1++) {
            for (int d2 = 0; d2 <= 9; d2++) {
                int cnt = 0;
                for (int j = 0; j < n; j++) {
                    if (cnt % 2 == 0 && d[j] == d1) cnt++;
                    else if (cnt % 2 == 1 && d[j] == d2) cnt++;
                }
                if (cnt&1) --cnt;
                ans = min(ans,n-cnt);
            }
        }
        cout << ans << '\n';
    }
}
