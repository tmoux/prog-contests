#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<vector<char>> g(n,vector<char>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> g[i][j];
      }
    }
    auto change = [n, &g](int mod1, int mod2) -> pair<int,vector<vector<char>>> {
      auto ret = g;
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (g[i][j] == 'X' && (i+j) % 3 == mod1) {
            ret[i][j] = 'O';
            cnt++;
          }
          else if (g[i][j] == 'O' && (i+j) % 3 == mod2) {
            ret[i][j] = 'X';
            cnt++;
          }
        }
      }
      return make_pair(cnt,ret);
    };
    pair<int,vector<vector<char>>> p = {n*n,{}};
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (i == j) continue;
        p = min(p,change(i,j));
      }
    }
    //output
    cerr << "cnt = " << p.first << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << p.second[i][j];
      }
      cout << '\n';
    }
  }
}
