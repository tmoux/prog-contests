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

const int maxn = 505;
int N, A[maxn];
int dp[2][maxn][maxn];
int dp2[maxn][maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
  }
  const int INF = 2e9;
  for (int j = 0; j <= N; j++) {
    for (int k = 0; k <= N; k++) {
      dp[0][j][k] = dp[1][j][k] = -INF;
      dp2[j][k] = -INF;
    }
  }
  dp[0][0][0] = 0;

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      for (int e = 0; e <= i-1; e++) {
        dp2[j][e] = dp[0][j][e];
        if (j > 0) ckmax(dp2[j][e], dp2[j-1][e]);
      }
    }
    for (int j = 1; j <= N; j++) {
      for (int e = 0; e <= i; e++) {
        ckmax(dp[1][j][e], dp[0][j][e] + A[j]);
        if (j >= i) {
          int need = j - i;
          if (e+need-1 >= 0) {
            ckmax(dp[1][j][e], dp2[j-1][e+need-1] + A[j]);
          }
        }
      }
    }
    swap(dp[0], dp[1]);
    for (int j = 0; j <= N; j++) {
      for (int e = 0; e <= N; e++) {
        dp[1][j][e] = -INF;
      }
    }
  }

  int ans = 0;
  for (int j = 1; j <= N; j++) {
    for (int e = 0; e <= N; e++) {
      ckmax(ans, dp[0][j][e]);
    }
  }
  cout << ans << '\n';
}
