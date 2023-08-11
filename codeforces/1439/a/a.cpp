#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n,vector<int>(m));
    for (int i = 0; i < n; i++) {
      string s; cin >> s;
      for (int j = 0; j < m; j++) {
        g[i][j] = s[j] == '1';
      }
    }
    vector<pair<int,int>> ans;
    auto flip = [&ans,&g](int i, int j) {
      g[i][j] ^= 1;
      ans.push_back({i+1,j+1});
    };
    for (int i = 0; i < n-2; i++) {
      for (int j = 0; j < m; j++) {
        if (j+1 < m && g[i][j] == 1 && g[i][j+1] == 1) {
          flip(i,j);
          flip(i,j+1);
          flip(i+1,j);
        }
        else if (g[i][j] == 1) {
          flip(i,j);
          flip(i+1,j);

          if (j < m-1) flip(i+1,j+1);
          else flip(i+1,j-1);
        }
      }
    }
    auto apply = [&g](vector<pair<int,int>> v) {
      for (auto p: v) {
        g[p.first][p.second] ^= 1;
      }
    };

    auto solve2 = [&flip,&apply,&ans,&g](int i, int j) {
      vector<vector<pair<int,int>>> v;
      v.push_back({{i,j},{i+1,j},{i,j+1}});
      v.push_back({{i+1,j},{i,j},{i+1,j+1}});
      v.push_back({{i,j+1},{i,j},{i+1,j+1}});
      v.push_back({{i+1,j+1},{i+1,j},{i,j+1}});

      int ret = 10;
      vector<pair<int,int>> r;
      for (int mask = 0; mask < (1<<4); mask++) {
        vector<pair<int,int>> u;
        int cnt = 0;
        for (int j = 0; j < 4; j++) {
          if (mask&(1<<j)) {
            cnt++;
            u.insert(u.end(),all(v[j]));
          }
        }
        apply(u);
        if (!g[i][j] && !g[i+1][j] && !g[i][j+1] && !g[i+1][j+1]) {
          if (ret > cnt) {
            ret = cnt;
            r = u;
          }
        }
        apply(u);
      }
      assert(ret <= 4);
      for (auto p: r) flip(p.first,p.second);
    };
    auto solve3 = [&flip,&apply,&ans,&g](int i, int j) {
      vector<vector<pair<int,int>>> v;
      v.push_back({{i,j},{i+1,j},{i,j+1}});
      v.push_back({{i+1,j},{i,j},{i+1,j+1}});
      v.push_back({{i,j+1},{i,j},{i+1,j+1}});
      v.push_back({{i+1,j+1},{i+1,j},{i,j+1}});

      v.push_back({{i,j+1},{i+1,j+1},{i,j+2}});
      v.push_back({{i+1,j+1},{i,j+1},{i+1,j+2}});
      v.push_back({{i,j+2},{i,j+1},{i+1,j+2}});
      v.push_back({{i+1,j+2},{i+1,j+1},{i,j+2}});

      int ret = 10;
      vector<pair<int,int>> r;
      for (int mask = 0; mask < (1<<8); mask++) {
        vector<pair<int,int>> u;
        int cnt = 0;
        for (int j = 0; j < 8; j++) {
          if (mask&(1<<j)) {
            cnt++;
            u.insert(u.end(),all(v[j]));
          }
        }
        apply(u);
        if (!g[i][j] && !g[i+1][j] && !g[i][j+1] && !g[i+1][j+1] && !g[i][j+2] && !g[i+1][j+2]) {
          if (ret > cnt) {
            ret = cnt;
            r = u;
          }
        }
        apply(u);
      }
      assert(ret <= 6);
      for (auto p: r) flip(p.first,p.second);
    };
    for (int j = 0; j < m; j += 2) {
      if (j+3 == m) {
        solve3(n-2,j);
        break;
      }
      else {
        solve2(n-2,j);
      }
    }

    assert((int)ans.size()/3 <= n*m);
    cout << ans.size()/3 << '\n';
    for (int i = 0; i < (int)ans.size(); i += 3) {
      cout << ans[i].first << ' ' << ans[i].second << ' ' << ans[i+1].first << ' ' << ans[i+1].second << ' ' << ans[i+2].first << ' ' << ans[i+2].second << '\n';
    }
    /*
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << g[i][j];
      }
      cout << '\n';
    }
    */
  }
}
