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
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
  return os << ']';
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

#define int ll
void solve() {
  string s; cin >> s;
  int N = sz(s);
  vector<int> v(N);
  F0R(i, N) v[i] = s[i] - 'A';
  const int val[] = {1, 10, 100, 1000, 10000};

  const int INF = 1e18;
  vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(2, vector<int>(1 << 5, -INF)));
  dp[N][0][0] = 0;
  for (int i = N-1; i >= 0; i--) {
    int x = val[v[i]];
    for (int t = 0; t < 2; t++) {
      for (int mask = 0; mask < (1 << 5); mask++) {
        bool isNeg = 0;
        for (int j = v[i]+1; j < 5; j++) {
          if (mask & (1 << j)) isNeg = 1;
        }
        ckmax(dp[i][t][mask | (1 << v[i])], dp[i+1][t][mask] + (isNeg ? -x : x));

        if (t == 1) {
          for (int nv = 0; nv < 5; nv++) {
            isNeg = 0;
            for (int j = nv+1; j < 5; j++) {
              if (mask & (1 << j)) isNeg = 1;
            }
            ckmax(dp[i][t][mask | (1 << nv)], dp[i+1][0][mask] + (isNeg ? -val[nv] : val[nv]));
          }
        }
      }
    }
  }

  int ans = -INF;
  for (int t = 0; t < 2; t++) {
    for (int mask = 0; mask < (1 << 5); mask++) {
      ckmax(ans, dp[0][t][mask]);
    }
  }
  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
