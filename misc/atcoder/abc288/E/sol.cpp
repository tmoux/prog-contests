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

const int maxn = 5005;
int N, M;
int X[maxn], isX[maxn];
int A[maxn], C[maxn];
int range[maxn][maxn];

ll dp[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  FOR(i, 1, N+1) cin >> A[i];
  FOR(i, 1, N+1) cin >> C[i];
  FOR(i, 1, M+1) {
    cin >> X[i];
    isX[X[i]] = 1;
  }

  FOR(i, 1, N+1) {
    range[i][0] = C[i];
    for (int j = 1; j <= N; j++) {
      if (i-j >= 1)
        range[i][j] = min(range[i][j-1], C[i-j]);
      else range[i][j] = range[i][j-1];
    }
  }

  for (int i = 1; i <= N+1; i++) {
    for (int b = 0; b <= N; b++) {
      dp[i][b] = 1e18;
    }
  }
  dp[1][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int b = 0; b < i; b++) {
      // cout << i << ' ' << b << ": " << dp[i][b] << endl;
      if (isX[i]) {
        ckmin(dp[i+1][b+1], dp[i][b] + A[i] + range[i][b]);
      }
      else {
        ckmin(dp[i+1][b+1], dp[i][b] + A[i] + range[i][b]);
        ckmin(dp[i+1][b], dp[i][b]);
      }
    }
  }

  ll ans = 1e18;
  for (int b = 0; b <= N; b++) {
    ckmin(ans, dp[N+1][b]);
  }
  cout << ans << '\n';
}
