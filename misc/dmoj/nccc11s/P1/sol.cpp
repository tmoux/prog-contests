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

const int maxn = 1e5+5;
int fib[maxn], comp[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int f0 = 0, f1 = 1;
  fib[f0] = 1;
  while (f1 < maxn) {
    fib[f1] = 1;
    int nf1 = f0 + f1;
    f0 = f1;
    f1 = nf1;
  }

  for (int i = 0; i < maxn; i++) {
    int x = i;
    bool p = false;

    int y = 0;
    int mult = 1;
    while (x > 0) {
      int d = x % 10;
      y += d * mult;
      x /= 10;
      mult *= 10;

      // cout << x << ' ' << y << endl;
      if (x > 0 && (fib[x] || comp[x]) && fib[y]) p = true;
    }

    if (p) comp[i] = 1;
  }

  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    cout << (comp[n] ? "YES" : "NO") << '\n';
  }
}
