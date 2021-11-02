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

void solve() {
  int N, M, A, B; cin >> N >> M >> A >> B;
  if (A - (N + M - 2) < 1 || B - (N + M - 2) < 1) {
    cout << "Impossible\n";
    return;
  }
  else {
    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (i == 0 || j == 0 || j == M-1) grid[i][j] = 1;
        else grid[i][j] = 1000;
      }
      grid[N-1][M-1] = A - (N + M - 2);
      grid[N-1][0] = B - (N + M - 2);
    }
    cout << "Possible\n";
    F0R(i, N) {
      F0R(j, M) {
        cout << grid[i][j] << ' ';
      }
      cout << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  for (int tc = 1; tc <= T; tc++) {
    cout << "Case #" << tc << ": ";
    solve();
  }
}
