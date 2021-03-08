#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 105;
const int INF = 2e9;
int X, Y;
string key;
int grid[maxn][maxn];

int dp[maxn][maxn][maxn];
int f(int i, int j, int k) {
  int& res = dp[i][j][k];
  if (res != -1) return res;
  if (i == Y-1 && j == X-1) return res = grid[i][j];
  res = INF;
  if (i+1 < Y) res = min(res,f(i+1,j,k));
  if (j+1 < X) res = min(res,f(i,j+1,k));
  if (k < key.size()) {
    int jmp = key[k]-'0';
    if (i+1+jmp < Y) res = min(res,f(i+1+jmp,j,k+1));
    if (j+1+jmp < X) res = min(res,f(i,j+1+jmp,k+1));
  }
  res += grid[i][j];
  return res;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> X >> Y;
  cin >> key;
  for (int i = 0; i < Y; i++) {
    for (int j = 0; j < X; j++) {
      char c; cin >> c;
      grid[Y-1-i][j] = c-'0';
    }
  }
  /*
  for (int i = 0; i < Y; i++) {
    for (int j = 0; j < X; j++) {
      cout << grid[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
  */
  memset(dp,-1,sizeof dp);
  int ans = f(0,0,0);
  cout << ans << '\n';
}
