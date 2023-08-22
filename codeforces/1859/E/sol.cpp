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

ll solve() {
  int N, K; cin >> N >> K;
  vector<ll> A(N+1), B(N+1);
  FOR(i, 1, N+1) cin >> A[i];
  FOR(i, 1, N+1) cin >> B[i];

  auto eval = [&](int i, int j) -> ll { // --, -+, +-, ++
    if (j == 0)      return -A[i] - B[i];
    else if (j == 1) return -A[i] + B[i];
    else if (j == 2) return +A[i] - B[i];
    else if (j == 3) return +A[i] + B[i];
    else assert(false);
  };
  auto flip = [&](int j) {
    assert(0 <= j && j < 4);
    if (j == 0) return 3;
    else if (j == 3) return 0;
    else return j;
  };

  const ll INF = 1e15;
  vector<vector<vector<ll>>> dp(4, vector<vector<ll>>(N+1, vector<ll>(N+1, -INF)));
  for (int i = 0; i < N; i++) {
    F0R(j, 4) dp[j][i][0] = eval(i+1, j);
  }
  vector<vector<ll>> DP(N+1, vector<ll>(N+1, -INF));

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    for (int k = 1; k <= i; k++) {
      ll tr = -INF;
      F0R(j, 4) {
        ckmax(tr, dp[j][i-1][k-1] + eval(i, flip(j)));
      }
      DP[i][k] = max(tr, DP[i-1][k]);
      if (k == K) ckmax(ans, DP[i][k]);
      if (i + 1 <= N) {
        F0R(j, 4) {
          ckmax(dp[j][i][k], max(dp[j][i-1][k-1], DP[i][k] + eval(i+1, j)));
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
