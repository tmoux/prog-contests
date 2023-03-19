#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args&&... args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

template <typename A, typename B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream& operator<<(ostream& os, const T_container& v) {
  os << '[';
  string sep;
  for (const T& x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

void solve() {
  int E, W;
  cin >> E >> W;
  vector<vector<int>> X(E, vector<int>(W));
  F0R(i, E) F0R(j, W) cin >> X[i][j];
  vector<vector<int>> dp(E, vector<int>(E));
  vector<vector<int>> C(E, vector<int>(E));
  F0R(i, E) {
    vector<int> count(W, 2e9);
    FOR(j, i, E) {
      F0R(k, W) ckmin(count[k], X[j][k]);
      C[i][j] = accumulate(all(count), 0);
    }
  }

  F0R(i, E) dp[i][i] = 2 * accumulate(all(X[i]), 0);
  for (int l = 1; l < E; l++) {
    for (int i = 0; i + l < E; i++) {
      int j = i + l;
      dp[i][j] = 2e9;
      for (int k = i; k < j; k++) {
        ckmin(dp[i][j], dp[i][k] + dp[k + 1][j] - 2 * C[i][j]);
      }
    }
  }

  cout << dp[0][E - 1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  FOR(tt, 1, T + 1) {
    cout << "Case #" << tt << ": ";
    solve();
  }
}