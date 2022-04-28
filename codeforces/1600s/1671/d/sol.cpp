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

const int maxn = 2e5 + 5;
int n, x;
int a[maxn];

ll dp[maxn][4][4];

int getLast(int last, int i) {
  if (last == 0) {
    assert(i != 0);
    return a[i - 1];
  } else if (last == 1)
    return 1;
  else if (last == 2)
    return x;
  else
    return -1;
}

ll f(int i, int left, int last) {
  ll &res = dp[i][left][last];
  if (res != -1) return res;
  if (i == n && left == 0) return 0;
  res = 1e18;
  if (i < n) {  // go next
    int add = last == 3 ? 0 : abs(a[i] - getLast(last, i));
    ckmin(res, f(i + 1, left, 0) + add);
  }
  if (left & 1) {
    int add = last == 3 ? 0 : abs(1 - getLast(last, i));
    ckmin(res, f(i, left ^ 1, 1) + add);
  }
  if (left & 2) {
    int add = last == 3 ? 0 : abs(x - getLast(last, i));
    ckmin(res, f(i, left ^ 2, 2) + add);
  }
  return res;
}

ll solve() {
  cin >> n >> x;
  F0R(i, n) cin >> a[i];
  F0R(i, n + 1) F0R(j, 4) F0R(k, 4) { dp[i][j][k] = -1; }
  ll ans = f(0, 3, 3);
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}

