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
int dp[maxn][maxn][2];

int f(int n, int m, int p) {
  int& res = dp[n][m][p];
  if (res != -1) return res;
  if (n == 1 && m == 1) return 0;
  if (p) {
    for (int i = 1; i < m; i++) {
      if (f(n, i, p^1)) {
        if (f(n, m-i, p)) return res = 1;
      }
      else {
        if (!f(n, m-i, p^1)) return res = 1;
      }
    }
  }
  else {
    for (int i = 1; i < n; i++) {
      if (f(i, m, p^1)) {
        if (f(n-i, m, p)) return res = 1;
      }
      else {
        if (!f(n-i, m, p^1)) return res = 1;
      }
    }
  }
  return res = 0;
}

void solve() {
  int N, M; cin >> N >> M;
  string s; cin >> s;
  int w = f(N, M, s == "Harry");
  cout << s << (w ? " can " : " cannot ") << "win\n";
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  memset(dp, -1, sizeof dp);
  int N = 20;
  F0R(i, N) {
    F0R(j, N) {
      cout << f(i, j, 0) << ' ';
    }
    cout << '\n';
  }
  return 0;
  int T; cin >> T;
  while (T--) solve();
}
