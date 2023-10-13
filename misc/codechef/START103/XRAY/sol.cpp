#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

// Assume N <= M. Then O(N^2*M) <= 10^5 * sqrt(10^5).
// Fix pair (r1, r2). Then we can find a list of crossing columns v = (c1, c2, ..., cn).
// Then we can process them left-to-right, keeping track of best one.
// Easy to write a brute force to check if necessary.

// Precompute:
// for each column, what is max down,
// for each row, what is max right

int solve() {
  int N, M; cin >> N >> M;
  vector<string> G(N);
  F0R(i, N) cin >> G[i];
  if (N > M) {
    swap(N, M);
    vector<string> nG(N, string(M, '#'));
    F0R(i, N) {
      F0R(j, M) {
        nG[i][j] = G[j][i];
      }
    }
    G = nG;
  }

  vector<vector<int>> sum(N, vector<int>(M));
  F0R(i, N) {
    F0R(j, M) {
      sum[i][j] = G[i][j] - '0';
      if (i > 0) sum[i][j] += sum[i-1][j];
      if (j > 0) sum[i][j] += sum[i][j-1];
      if (i > 0 && j > 0) sum[i][j] -= sum[i-1][j-1];
    }
  }

  vector<vector<int>> maxRight(N, vector<int>(M));
  F0R(i, N) {
    F0Rd(j, M) {
      if (G[i][j] == '1') {
        maxRight[i][j] = j;
        if (j + 1 < M && G[i][j+1] == '1') {
          maxRight[i][j] = maxRight[i][j+1];
        }
      }
    }
  }
  vector<vector<int>> maxDown(N, vector<int>(M));
  F0R(j, M) {
    F0Rd(i, N) {
      // cout << i << ' ' << j << ": " << G[i][j] << endl;
      if (G[i][j] == '1') {
        maxDown[i][j] = i;
        if (i + 1 < N && G[i+1][j] == '1') {
          maxDown[i][j] = maxDown[i+1][j];
        }
      }
    }
  }

  auto getsum = [&](int r1, int c1, int r2, int c2) -> int {
    if (r1 > r2 || c1 > c2) return 0;
    int ans = sum[r2][c2];
    if (r1-1 >= 0) ans -= sum[r1-1][c2];
    if (c1-1 >= 0) ans -= sum[r2][c1-1];
    if (r1-1 >= 0 && c2-1 >= 0) ans += sum[r1-1][c1-1];
    return ans;
  };
  auto can_reach = [&](int r1, int r2, int c1, int c2) -> bool {
    assert(G[r1][c1] == '1' && G[r2][c1] == '1');
    return maxRight[r1][c1] >= c2 && maxRight[r2][c1] >= c2;
  };
  auto crossing_col = [&](int r1, int r2, int j) -> bool {
    return G[r1][j] == '1' && maxDown[r1][j] >= r2;
  };

  int ans = 0;
  F0R(r1, N) {
    FOR(r2, r1+2, N) {
      vector<int> v;
      F0R(j, M) {
        if (crossing_col(r1, r2, j)) v.push_back(j);
      }
      if (!v.empty()) {
        vector<int> mxj(sz(v));
        mxj[sz(v)-1] = v.back();
        for (int i = sz(v)-2; i >= 0; i--) {
          if (can_reach(r1, r2, v[i], v[i+1])) {
            mxj[i] = mxj[i+1];
          }
          else mxj[i] = v[i];
          ckmax(ans, getsum(r1+1, v[i]+1, r2-1, mxj[i]-1));
        }
      }
    }
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
