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

const int MOD = 998244353;

const int maxn = 5005;
int rows[maxn][maxn], cols[maxn][maxn];

inline void madd(int& a, int b) {
  a += b;
  if (a >= MOD) a -= MOD;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;

  int ans = 0;
  for (int i = 0; i < N - 1; i++) {
    for (int j = i; j < N - 1; j++) {
      if (i > 0) madd(cols[i][j], cols[i-1][j]);
      if (j > 0) madd(rows[i][j], rows[i][j-1]);
      int x = i == 0 && j == 0 ? 1 : 0;
      madd(x, rows[i][j]);
      madd(x, cols[i][j]);
      // cout << i << ' ' << j << ": " << dp[i][j] << endl;
      madd(rows[i][j+1], x);
      if (j+1+K < maxn) madd(rows[i][j+1+K], MOD-x);

      madd(cols[j+1][j], x);
      if (max(i+1+K, j+1) < maxn) madd(cols[max(i+1+K, j+1)][j], MOD-x);

      if (i < j) {
        swap(i, j);
        madd(rows[i][i+1], x);
        if (max(j+1+K, i+1) < maxn) madd(rows[i][max(j+1+K, i+1)], MOD-x);
        swap(i, j);
      }

      if ((i > 0 || j > 0) && N-1-i <= K && N-1-j <= K) madd(ans, x);
    }
  }

  madd(ans, ans);
  if (K == N-1) madd(ans, 1);

  cout << ans << '\n';
}
