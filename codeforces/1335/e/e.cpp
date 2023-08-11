#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<vector<int>> left_freq(201,vector<int>(1,-1)), right_freq(201,vector<int>(1,-1));
        vector<vector<int>> freq(201,vector<int>(n,0));
        vector<int> mp(201,0);
        for (int i = 0; i < n; i++) {
            left_freq[a[i]].push_back(i);
            ++freq[a[i]][i];
            for (int j = 1; j <= 200; j++) {
                if (i > 0) freq[j][i] += freq[j][i-1];
            }
        }
        mp = vector<int>(201,0);
        for (int i = n-1; i >= 0; i--) {
            right_freq[a[i]].push_back(i);
            ++mp[a[i]];
        }
        int ans = 0;
        for (int a = 1; a <= 200; a++) {
            ans = max(ans,mp[a]);
        }
        for (int a = 1; a <= 200; a++) {
            for (int x = 1; ; x++) {
                if (x >= left_freq[a].size()) break;
                int l = left_freq[a][x], r = right_freq[a][x];
                if (l == -1 || r == -1 || l >= r) break;
                int y = 0;
                for (int b = 1; b <= 200; b++) {
                    y = max(y,freq[b][r-1]-freq[b][l]);
                }
                ans = max(ans,2*x+y);
            }
        }
        cout << ans << '\n';
    }
}
