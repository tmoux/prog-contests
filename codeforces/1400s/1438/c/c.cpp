#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, m; cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m,0));
    map<int,vector<pair<int,int>>> mp;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> a[i][j];
        mp[a[i][j]].push_back({i,j});
      }
    }
    for (auto p: mp) {
      int f = p.first; 
      for (auto q: p.second) {
        int i = q.first;
        int j = q.second;
        if ((f^(i+j))&1) {
          a[i][j]++;
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << a[i][j] << ' ';
      }
      cout << '\n';
    }
  }
}

