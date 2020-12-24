#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int n = 97;
char grid[n][n];
char grid2[n][n];

bool same() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] != grid2[i][j]) return false;
    }
  }
  return true;
}

int dx[] = {-1,-1,-1,0,0,1,1,1};
int dy[] = {-1,0,1,-1,1,-1,0,1};

bool valid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < n;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }
  while (true) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (grid[i][j] == '.') {
          grid2[i][j] = '.';
        }
        else if (grid[i][j] == 'L') {
          int cnt = 0;
          for (int k = 0; k < 8; k++) {
            int xx = i + dx[k];
            int yy = j + dy[k];
            if (valid(xx,yy) && grid[xx][yy] == '#') {
              cnt++;
            }
          }
          if (cnt > 0) {
            grid2[i][j] = 'L';
          }
          else {
            grid2[i][j] = '#';
          }
        }
        else {
          int cnt = 0;
          for (int k = 0; k < 8; k++) {
            int xx = i + dx[k];
            int yy = j + dy[k];
            if (valid(xx,yy) && grid[xx][yy] == '#') {
              cnt++;
            }
          }
          if (cnt >= 4) {
            grid2[i][j] = 'L';
          }
          else {
            grid2[i][j] = '#';
          }
        }
      }
    }
    if (same()) break;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        grid[i][j] = grid2[i][j];
        cout << grid2[i][j];
      }
      cout << '\n';
    }
    cout << '\n';
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      //cout << grid2[i][j];
      if (grid[i][j] == '#') ans++;
    }
    //cout << '\n';
  }
  cout << "ans " << ans << endl;
}
