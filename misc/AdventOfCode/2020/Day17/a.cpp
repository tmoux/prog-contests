#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n = 8;
  vector<vector<vector<vector<char>>>> g(30,vector<vector<vector<char>>>(30,vector<vector<char>>(30,vector<char>(30))));
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < n; j++) {
      g[15+i][15+j][15][15] = s[j];
    }
  }
  auto valid = [](int i, int j, int k, int l) {
    return 0 <= i && i < 30 && 0 <= j && j < 30 && 0 <= k && k < 30 && 0 <= l && l < 30;
  };
  for (int iter = 0; iter < 6; iter++) {
    auto gg = g;
    for (int i = 0; i < 30; i++) {
      for (int j = 0; j < 30; j++) {
        for (int k = 0; k < 30; k++) {
          for (int l = 0; l < 30; l++) {
            int neighbors = 0;
            for (int dx = -1; dx <= 1; dx++) {
              for (int dy = -1; dy <= 1; dy++) {
                for (int dz = -1; dz <= 1; dz++) {
                  for (int dw = -1; dw <= 1; dw++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0) continue;
                    if (!valid(i+dx,j+dy,k+dz,l+dw)) continue;
                    if (g[i+dx][j+dy][k+dz][l+dw] == '#') {
                      neighbors++;
                    }
                  }
                }
              }
            }
            if (g[i][j][k][l] == '#') {
              if (neighbors == 2 || neighbors == 3) {
                gg[i][j][k][l] = '#';
              }
              else {
                gg[i][j][k][l] = '.';
              }
            }
            else {
              if (neighbors == 3) {
                gg[i][j][k][l] = '#';
              }
              else {
                gg[i][j][k][l] = '.';
              }
            }
          }
        }
      }
    }
    g = gg;
  }
  int ans = 0;
  for (int i = 0; i < 30; i++) {
    for (int j = 0; j < 30; j++) {
      for (int k = 0; k < 30; k++) {
        for (int l = 0; l < 30; l++) {
          if (g[i][j][k][l] == '#') ans++;
        }
      }
    }
  }
  cout << ans << '\n';
}
