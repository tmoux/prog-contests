#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll
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

int f(int l, int r, const vector<int>& A) {
  if (r-l+1 < 3) return -1e9;
  int m = (l+r)/2;
  int ans = -1e9;

  int rmx = -1e9;
  for (int i = m+1; i <= r; i++) {
    ckmax(rmx, A[i] - i);
  }
  int midmx = -1e9;
  for (int i = m-1; i >= l; i--) {
    ckmax(midmx, A[i+1]);
    int tr = A[i] + i + midmx + rmx;
    ckmax(ans, tr);
  }

  {
    int lmx = -1e9;
    for (int i = m; i >= l; i--) {
      ckmax(lmx, A[i] + i);
    }
    midmx = -1e9;
    for (int i = m+2; i <= r; i++) {
      ckmax(midmx, A[i-1]);
      int tr = lmx + midmx + A[i] - i;
      ckmax(ans, tr);
    }
  }

  ckmax(ans, f(l, m, A));
  ckmax(ans, f(m+1, r, A));
  return ans;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  int ans = f(0, N-1, A);
  cout << ans << '\n';
}

int32_t main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
