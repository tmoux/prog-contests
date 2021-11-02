#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

template<typename T>
T maxv(T a) {
  return a;
}
template<typename T, typename ... Args>
T maxv(T a, Args ... args) {
  return std::max(a, maxv(args...));
}

template<typename T>
T minv(T a) {
  return a;
}
template<typename T, typename ... Args>
T minv(T a, Args ... args) {
  return std::min(a, minv(args...));
}

#define DEBUG(x) cerr << #x << ": " << x << '\n'

const int maxn = 1005;
bool grid[maxn][maxn]; //false = blocked
int dp[2][maxn][maxn]; //0 = right, 1 = down

int numActive = 0;
int total = 0;

void update(int d, int i, int j, int x) {
  int diff = x - dp[d][i][j];
  total += diff;
  dp[d][i][j] = x;
}

void block_zigzag(int i, int j, int d, int dir) {
  if (i < 0 || j < 0) return;
  if (!grid[i][j]) return;
  update(dir, i, j, d);
  if (dir == 0) {
    block_zigzag(i, j-1, d+1, dir^1);
  }
  else {
    block_zigzag(i-1, j, d+1, dir^1);
  }
}

void unblock_zigzag(int i, int j, int x, int d, int dir) {
  if (i < 0 || j < 0) return;
  if (!grid[i][j]) return;
  update(dir, i, j, dp[dir][i][j] + x);
  if (dir == 0) {
    unblock_zigzag(i, j-1, x, d+1, dir^1);
  }
  else {
    unblock_zigzag(i-1, j, x, d+1, dir^1);
  }
}

void block(int i, int j) {
  update(0, i, j, 0);
  update(1, i, j, 0);
  block_zigzag(i-1, j, 1, 0);
  block_zigzag(i, j-1, 1, 1);
}

void unblock(int i, int j) {
  update(0, i, j, 1 + dp[1][i+1][j]);
  update(1, i, j, 1 + dp[0][i][j+1]);
  unblock_zigzag(i-1, j, dp[1][i][j], 1, 0);
  unblock_zigzag(i, j-1, dp[0][i][j], 1, 1);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, m, q; cin >> n >> m >> q;

  F0Rd(i, n) F0Rd(j, m) {
    grid[i][j] = true;
    numActive++;
    unblock(i, j);
  }

  while (q--) {
    int x, y; cin >> x >> y;
    x--; y--;

    if (grid[x][y]) {
      grid[x][y] = false;
      block(x, y);
      numActive--;
    }
    else {
      grid[x][y] = true;
      unblock(x, y);
      numActive++;
    }
    cout << (total - numActive) << '\n';
  }
}
