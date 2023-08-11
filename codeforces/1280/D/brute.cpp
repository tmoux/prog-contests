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
  int N, M; cin >> N >> M;
  vector<ll> X(N);
  F0R(i, N) {
    int x; cin >> x;
    X[i] = -x;
  }
  F0R(i, N) {
    int x; cin >> x;
    X[i] += x;
  }
  vector<vector<int>> adj(N);
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  const ll INF = 1e16;
  vector<vector<array<ll, 2>>> dp(N);
  vector<int> sub_size(N);
  auto dfs = y_combinator([&](auto dfs, int i, int p) -> void {
    sub_size[i] = 1;
    dp[i].resize(2, {-INF, -INF});
    dp[i][1] = {0, X[i]};
    for (int j: adj[i]) {
      if (j == p) continue;
      dfs(j, i);
      sub_size[i] += sub_size[j];
      vector<array<ll, 2>> ndp(sub_size[i]+1, {-INF, -INF});
      for (int x = 1; x <= sub_size[i]-sub_size[j]; x++) {
        for (int y = 1; y <= sub_size[j] && x + y <= sub_size[i]; y++) {
          // if cutoff edge:
          ckmax(ndp[x+y], {dp[i][x][0] + dp[j][y][0] + (dp[j][y][1] > 0),
                           dp[i][x][1]});
          // if merge top together:
          ll nbal = dp[i][x][1] + dp[j][y][1];
          ll nc = dp[i][x][0] + dp[j][y][0];
          ckmax(ndp[x+y-1], {nc, nbal});
        }
      }
      dp[i] = ndp;
    }
  });
  dfs(0, 0);
  return (dp[0][M][0] + (dp[0][M][1] > 0));
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
