#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    vector<vector<char>> grid(n,vector<char>(m));
    vector<vector<int>> cnt(n,vector<int>(m,0));
    vector<pair<int,int>> v, nv;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
        if (grid[i][j] == '*') {
          v.push_back({i,j});
          ans++;
          cnt[i][j]++;
        }
        if (j > 0) cnt[i][j] += cnt[i][j-1];
      }
    }
    auto rowsum = [&cnt,n,m](int row, int l, int r) {
      return cnt[row][r]-(l==0?0:cnt[row][l-1]);
    };
    for (int k = 1; !v.empty(); k++) {
      for (auto p: v) {
        int l = p.second-k;
        int r = p.second+k;
        int row = p.first+k;
        if (0 <= l && r < m && row < n) {
          if (rowsum(row,l,r) == 2*k+1) {
            nv.push_back(p);
            ans++;
          }
        }
      }
      v = nv;
      nv.clear();
    }
    cout << ans << '\n';
  }
}

