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

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename T>
ostream& operator<<(ostream& o, const vector<T>& v) {
  o << "[";
  for (auto it = v.begin(); it != v.end(); ++it) {
    o << *it; if (next(it) != v.end()) o << ", ";
  }
  o << "]";
  return o;
}

int calc(int R, int C, int K, const vector<vector<char>>& grid) {
  vector<vector<int>> sum(R, vector<int>(C, 0));
  F0R(j, C) sum[0][j] = grid[0][j] == 'X' ? 1 : 0;
  FOR(i, 1, R) {
    F0R(j, C) {
      sum[i][j] = sum[i-1][j] + (grid[i][j] == 'X' ? 1 : 0);
    }
  }
  int ans = C;

  /*
  cout << "K = " << K << endl;
  F0R(i, R) {
    F0R(j, C) {
      cout << grid[i][j];
    }
    cout << '\n';
  }
  */

  FOR(i, K, R+K) {
    int tr = i - K;
    F0R(j, C) {
      if (sum[min(R-1,i)][j] >= K+1 || (i < R && grid[i][j] == 'X')) 
        tr++;
    }
    //cout << i << ": " << tr << endl;
    ckmin(ans, tr);
  }
  return ans;
}

int solve() {
  int R, C, K; cin >> R >> C >> K;
  K--;
  vector<vector<char>> grid(R, vector<char>(C));
  F0R(i, R) {
    F0R(j, C) {
      cin >> grid[i][j];
    }
  }
  
  int ans = C;
  ckmin(ans, calc(R, C, K, grid));
  reverse(all(grid));
  K = R - 1 - K;
  ckmin(ans, calc(R, C, K, grid));

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
