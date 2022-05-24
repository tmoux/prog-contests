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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, q; cin >> n >> q;
  set<int> xs, ys;
  map<int,int> cntX, cntY;
  for (int i = 1; i <= n; i++) {
    xs.insert(i);
    ys.insert(i);
  }
  while (q--) {
    int t; cin >> t;
    if (t == 1) {
      int x, y; cin >> x >> y;
      if (cntX[x]++ == 0) {
        xs.erase(x);
      }
      if (cntY[y]++ == 0) {
        ys.erase(y);
      }
    }
    else if (t == 2) {
      int x, y; cin >> x >> y;
      if (--cntX[x] == 0) {
        xs.insert(x);
      }
      if (--cntY[y] == 0) {
        ys.insert(y);
      }
    }
    else {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      bool poss1 = true;
      auto it = xs.lower_bound(x1);
      if (it != xs.end() && *it <= x2) poss1 = false;
      it = xs.upper_bound(x2);
      if (it != xs.begin() && *prev(it) >= x1) poss1 = false;

      bool poss2 = true;
      it = ys.lower_bound(y1);
      if (it != ys.end() && *it <= y2) poss2 = false;
      it = ys.upper_bound(y2);
      if (it != ys.begin() && *prev(it) >= y1) poss2 = false;

      cout << (poss1 || poss2 ? "Yes" : "No") << '\n';
    }
  }
}
