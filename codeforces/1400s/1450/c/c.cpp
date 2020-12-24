#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve(vector<vector<char>>& g, int ii, int jj) {
  vector<int> rows, cols;
  for (int i = ii; i < ii+3; i++) {
    bool flag = true;
    for (int j = jj; j < jj+3; j++) {
      if (g[i][j] != 'X') flag = false;
    }
    if (flag) rows.push_back(i);
  }
  for (int j = jj; j < jj+3; j++) {
    bool flag = true;
    for (int i = ii; i < ii+3; i++) {
      if (g[i][j] != 'X') flag = false;
    }
    if (flag) cols.push_back(j);
  }
  reverse(cols.begin(),cols.end());
  while (!rows.empty() && !cols.empty()) {
    int i = rows.back(); rows.pop_back();
    int j = cols.back(); cols.pop_back();
    g[i][j] = 'O';
  }
  while (!rows.empty()) {
    int i = rows.back(); rows.pop_back();
    g[i][jj+2] = 'O';
  }
  while (!cols.empty()) {
    int j = cols.back(); cols.pop_back();
    g[ii+2][j] = 'O';
  }
}

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
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (j-2 >= 0 && g[i][j] == 'X' && g[i][j-1] == 'X' && g[i][j-2] == 'X') {
          g[i][j] = 'O';
        }
        else if (i-2 >= 0 && g[i][j] == 'X' && g[i-1][j] == 'X' && g[i-2][j] == 'X') {
          g[i][j] = 'O';
        }
        else if (i-1 >= 0 && i+1 < n && j-1 >= 0 && j+1 < n && g[i][j] == 'X' && g[i+1][j] == 'X' && g[i-1][j] == 'X' && g[i][j-1] == 'X' && g[i][j+1] == 'X') {
          g[i][j] = 'O';
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << g[i][j];
      }
      cout << '\n';
    }
  }
}

