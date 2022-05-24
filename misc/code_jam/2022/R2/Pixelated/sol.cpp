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

void solve() {
  int R; cin >> R;
  int missing = 0;
  vector<vector<bool>> g(R+1, vector<bool>(R+1, false));
  vector<vector<bool>> h(R+1, vector<bool>(R+1, false));
  for (int x = 0; x <= R; x++) {
    for (int y = 0; y <= R; y++) {
      if (round(sqrt(x*x + y*y)) <= R) {
        g[x][y] = true;
      }
    }
  }
  for (int r = 0; r <= R; r++) {
    for (int x = 0; x <= r; x++) {
      int y = round(sqrt(r*r - x*x));
      h[x][y] = h[y][x] = true;
    }
  }
  for (int x = 0; x <= R; x++) {
    for (int y = 0; y <= R; y++) {
      if (g[x][y] && !h[x][y]) {
        missing++;
      }
    }
  }
  missing *= 4;
  cout << missing << '\n';
  /*
  for (int x = 0; x <= R; x++) {
    int mxy = 0;
    while (round(sqrt(x*x + mxy*mxy)) <= R) mxy++;
    vector<bool> cnt(mxy, false);
    for (int r = x; r <= R; r++) {
      int y = round(sqrt(r*r - x*x));
      cnt[y] = true;
    }
    cout << x << ": " << mxy-1 << endl;
    for (int y = 0; y < mxy; y++) {
      if (!cnt[y]) {
        cout << x << ' ' << y << endl;
        missing++;
      }
    }
  }
  missing *= 4;
  cout << missing << '\n';
  */
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  FOR(tt, 1, T+1) {
    cout << "Case #" << tt << ": ";
    solve();
  }
}
