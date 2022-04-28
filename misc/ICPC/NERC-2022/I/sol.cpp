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

int scan(int i, int j) {
  cout << "SCAN " << i << ' ' << j << endl;
  int x; cin >> x;
  return x;
}

int dig(int i, int j) {
  cout << "DIG " << i << ' ' << j << endl;
  int x; cin >> x;
  return x;
}

void solve() {
  int n, m; cin >> n >> m;

  int s1 = scan(1, 1);
  int s2 = scan(1, m);
  int x_sum = (s1 + s2 + 6 - 2 * m) / 2;
  int y_sum = s1 - x_sum + 4;

  int s3 = scan(x_sum / 2, 1);
  int x_diff = s3 - y_sum + 2;
  int x1 = (x_sum + x_diff) / 2;
  int x2 = (x_sum - x_diff) / 2;

  int s4 = scan(1, y_sum / 2);
  int y_diff = s4 - x_sum + 2;
  int y1 = (y_sum + y_diff) / 2;
  int y2 = (y_sum - y_diff) / 2;

  if (dig(x1, y1)) {
    dig(x2, y2);
  } else {
    dig(x1, y2);
    dig(x2, y1);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}

