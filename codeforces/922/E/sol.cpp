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

const int maxn = 1005, maxc = 10005;
int N, W, B, X;
int cnt[maxn], cost[maxn];

ll dp[maxn][maxc];

ll cap(int c) {
  return W + 1LL * c * B;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> W >> B >> X;
  FOR(i, 1, N+1) cin >> cnt[i];
  FOR(i, 1, N+1) cin >> cost[i];

  memset(dp, -1, sizeof dp);
  dp[0][0] = W;
  FOR(i, 1, N+1) {
    F0R(c, maxc) {
      if (dp[i-1][c] > -1) {
        ckmax(dp[i][c], min(cap(c), dp[i-1][c] + (i == 1 ? 0 : X)));
      }
    }
    F0Rd(c, maxc) {
      for (int k = 0; k <= cnt[i] && k <= c; k++) {
        if (dp[i][c-k] >= 1LL*k*cost[i]) {
          ckmax(dp[i][c], dp[i][c-k] - 1LL*k*cost[i]);
        }
      }
    }
  }

  F0Rd(c, maxc) {
    if (dp[N][c] > -1) {
      cout << c << '\n';
      return 0;
    }
  }
}
