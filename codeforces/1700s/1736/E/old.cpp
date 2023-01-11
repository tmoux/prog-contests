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
int sum[maxn];
int dp[maxn][maxn][maxn][2];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N) {
    cin >> A[i];
    sum[i] = A[i] + (i == 0 ? 0 : sum[i-1]);
  }
  const int INF = 2e9;
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= N; j++) {
      for (int k = 0; k <= N; k++) {
        dp[i][j][k][0] = dp[i][j][k][1] = -INF;
      }
    }
  }
  // 0 = normal, can move, 1 = can't take
  dp[0][0][0][0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      for (int e = 0; e < N; e++) {
        for (int d: {0, 1}) {
          int res = dp[i][j][e][d];
          ckmax(dp[i+1][j][e][0], res + A[j]);
          if (!d) ckmax(dp[i+1][i+1][e+1][d], res + A[j]);
          for (int ii = i+1; ii < N && (e-(ii-(i+1))) >= 0; ii++) {
            // if (ii == 4 && (e-(ii-(i+1))) == 0) {
            //   cout << "adding from " << i << ' ' << j << ' ' << e << ": " << dp[i][j][e] << ' ' << A[ii] * (ii - i) << endl;
            // }
            ckmax(dp[ii][ii][e-(ii-(i+1))][1], res + A[ii] * (ii-i));
          }
        }
      }
    }
  }

  // DEBUG(dp[1][1][0]);
  // DEBUG(dp[3][1][0]);
  // DEBUG(dp[4][4][0]);

  F0R(i, N+1) {
    F0R(j, N+1) {
      F0R(e, N+1) {
        for (int d: {0, 1}) {
          cout << i << ' ' << j << ' ' << e << ' ' << d << ": " << dp[i][j][e][d] << '\n';
        }
      }
    }
  }

  int ans = 0;
  for (int j = 0; j <= N; j++) {
    for (int e = 0; e <= N; e++) {
      ckmax(ans, dp[N][j][e][0]);
    }
  }
  cout << ans << '\n';
}
