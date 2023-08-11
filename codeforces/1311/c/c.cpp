#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        string s; cin >> s;
        vector<int> p(m);
        for (int i = 0; i < m; i++) {
            cin >> p[i];
        }
        p.push_back(n);
        vector<vector<int>> pfx(26,vector<int>(n,0));
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < n; j++) {
                pfx[i][j] = j == 0 ? 0 : pfx[i][j-1];
                if (s[j]-'a' == i) ++pfx[i][j];
            }
        }
        vector<ll> ans(26);
        for (int i = 0; i < p.size(); i++) {
            for (int j = 0; j < 26; j++) {
                ans[j] += pfx[j][p[i]-1];
            }
        }
        for (int i = 0; i < 26; i++) {
            cout << ans[i] << ' ';
        }
        cout << '\n';
    }
}

