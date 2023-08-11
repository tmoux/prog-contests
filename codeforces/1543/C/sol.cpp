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

// #define double long double

void solve() {
  double c, m, p, v; cin >> c >> m >> p >> v;

  double ans = 0;
  for (int len = 0; len <= 18; len++) {
    F0R(mask, 1 << len) {
      double prob = 1;
      double x = c, y = m, z = p;
      const double eps = 1e-12;
      F0R(i, len) {
        // if (len == 2 && mask == 2) {
        //   cout << x << ' ' << y << ' ' << z << endl;
        // }
        if (mask & (1 << i)) {
          prob *= x;
          if (x <= v) {
            if (y > eps) {
              y += x / 2;
              z += x / 2;
            }
            else z += x;
            x = 0;
          }
          else {
            x -= v;
            if (y > eps) {
              y += v / 2;
              z += v / 2;
            }
            else z += v;
          }
        }
        else {
          prob *= y;
          if (y <= v) {
            if (x > eps) {
              x += y / 2;
              z += y / 2;
            }
            else z += y;
            y = 0;
          }
          else {
            y -= v;
            if (x > eps) {
              x += v / 2;
              z += v / 2;
            }
            else z += v;
          }
        }
        // assert(abs(x + y + z - 1) < eps);
        if (prob < eps) break;
      }
      // if (len == 2 && mask == 2) {
      //   cout << x << ' ' << y << ' ' << z << endl;
      // }
      prob *= z;

      // if (prob > eps) {
      //   // cout << 1+len << ": " << prob << ' ' << (1+len)*prob << endl;
      //   // DEBUG(mults);
      // }
      ans += (1 + len) * prob;
    }
  }

  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cout << fixed << setprecision(10);
  int T; cin >> T;
  while (T--) solve();
}
