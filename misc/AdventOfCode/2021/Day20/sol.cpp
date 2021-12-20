#include <bits/stdc++.h>
 
using namespace std;

int main() {
  string code; cin >> code;

  int n = 100;
  vector<vector<char>> grid(3*n, vector<char>(3*n, '.'));
  for (int i = 0; i < n; i++) {
    string line; cin >> line;
    for (int j = 0; j < n; j++) {
      grid[i+n][j+n] = line[j];  
    }
  }

  auto valid = [&](int i, int j) {
    return 0 <= i && i < 3*n && 0 <= j && j < 3*n;
  };

  int iter = 50;
  for (int it = 0; it < iter; it++) {
    vector<vector<char>> ngrid(3*n, vector<char>(3*n, '.'));
    for (int i = 0; i < 3*n; i++) {
      for (int j = 0; j < 3*n; j++) {
        int pt = 8;
        int val = 0;
        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            int ni = i + dx;
            int nj = j + dy;
            char c = valid(ni, nj) ? grid[ni][nj] : it % 2 == 0 ? '.' : '#';

            if (c == '#') {
              val |= 1<<pt;
            }
            pt--;
          }
        }
        ngrid[i][j] = code[val];
      }
    }
    grid = ngrid;
  }

  int cnt = 0;
  for (int i = 0; i < 3*n; i++) {
    for (int j = 0; j < 3*n; j++) {
      if (grid[i][j] == '#') cnt++;
    }
  }
  cout << cnt << endl;
}
