#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

ll solve() {
  int N, M; cin >> N >> M;
  vector<vector<ll>> A(N, vector<ll>(M));
  F0R(i, N) {
    F0R(j, M) {
      cin >> A[i][j];
    }
  }

  vector<vector<ll>> c1(N, vector<ll>(M)); // max reward from top corner
  F0R(i, N) {
    F0R(j, M) {
      c1[i][j] = A[i][j];
      if (i > 0) ckmax(c1[i][j], A[i][j] + c1[i-1][j]);
      if (j > 0) ckmax(c1[i][j], A[i][j] + c1[i][j-1]);
    }
  }
  vector<vector<ll>> c2(N, vector<ll>(M)); // max reward to bottom corner
  F0Rd(i, N) {
    F0Rd(j, M) {
      c2[i][j] = A[i][j];
      if (i + 1 < N) ckmax(c2[i][j], A[i][j] + c2[i+1][j]);
      if (j + 1 < M) ckmax(c2[i][j], A[i][j] + c2[i][j+1]);
    }
  }
  auto getc1 = [&](int i, int j) -> ll {
    if (0 <= i && i < N && 0 <= j && j < M) return c1[i][j];
    return 0;
  };
  auto getc2 = [&](int i, int j) -> ll {
    if (0 <= i && i < N && 0 <= j && j < M) return c2[i][j];
    return 0;
  };
  auto c1max = [&](int i, int j) -> ll {
    return max(getc1(i-1, j), getc1(i, j-1));
  };
  auto c2max = [&](int i, int j) -> ll {
    return max(getc2(i+1, j), getc2(i, j+1));
  };

  const ll INF = 1e18;
  vector<vector<ll>> dpH(N, vector<ll>(M, INF)); // end on horizontal
  vector<vector<ll>> dpV(N, vector<ll>(M, INF)); // end on vertical

  F0R(i, N) {
    F0Rd(j, M) {
      if (i == 0 && j == M-1) {
        dpH[i][j] = dpV[i][j] = 0;
      }
      ll midcost = 0;
      for (int nj = j+1; nj < M; nj++) {
        ckmin(dpH[i][j], max({
            dpV[i][nj],
            c1max(i, j) + c2max(i, nj),
            midcost}));
        ckmax(midcost, max(c1max(i, j), getc1(i-1, nj)) + getc2(i+1, nj));
      }

      midcost = 0;
      for (int ni = i-1; ni >= 0; ni--) {
        ckmin(dpV[i][j], max({
            dpH[ni][j],
            c1max(ni, j) + c2max(i, j),
            midcost}));
        ckmax(midcost, getc1(ni, j-1) + max(getc2(ni, j+1), c2max(i, j)));
      }
    }
  }
  return min(dpH[N-1][0], dpV[N-1][0]);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tc, 1, T+1) {
    cout << "Case #" << tc << ": " << solve() << '\n';
  }
}
