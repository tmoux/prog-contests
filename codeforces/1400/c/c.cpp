#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int n = s.size();
        int x; cin >> x;
        vector<int> ans(n,1);
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                if (i-x >= 0) ans[i-x] = 0;
                if (i+x < n) ans[i+x] = 0;
            }
        }
        bool poss = true;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                if ((i-x < 0  || ans[i-x] == 0) &&
                    (i+x >= n || ans[i+x] == 0)) {
                    poss = false;
                    break;
                }
            }
        }
        if (!poss) {
            cout << -1 << '\n';
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << ans[i];
            }
            cout << '\n';
        }
    }
}

