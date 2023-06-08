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

void solve() {
  int N, M; cin >> N >> M;
  map<int, vector<pair<int, int>>> shots;
  int R; cin >> R;
  REP(R) {
    int t, d, x; cin >> t >> d >> x;
    shots[t].push_back({d, x});
  }

  int ans = 2e9;
  vector<vector<vector<int>>> dp(2, vector<vector<int>>(N+1, vector<int>(M+1)));
  dp[0][0][0] = 1;
  for (int t = 1; ; t++) {
    F0R(i, N+1) {
      F0R(j, M+1) {
        dp[1][i][j] = dp[0][i][j];
        if (i > 0) dp[1][i][j] |= dp[0][i-1][j];
        if (j > 0) dp[1][i][j] |= dp[0][i][j-1];
      }
    }
    auto v = shots[t];
    for (auto [d, x]: v) {
      if (d == 1) {
        for (int j = 0; j <= M; j++) {
          dp[1][x][j] = 0;
        }
      }
      else {
        for (int j = 0; j <= N; j++) {
          dp[1][j][x] = 0;
        }
      }
    }
    // DEBUG(t);
    // F0R(i, N+1) {
    //   F0R(j, M+1) {
    //     cout << dp[1][i][j] << ' ';
    //   }
    //   cout << endl;
    // }

    if (dp[1][N][M]) {
      ans = t;
      break;
    }
    swap(dp[0], dp[1]);
    bool p = 0;
    F0R(i, N+1) {
      F0R(j, M+1) {
        dp[1][i][j] = 0;
        p |= dp[0][i][j];
      }
    }
    if (!p) break;
  }
  cout << (ans < 2e9 ? ans : -1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
