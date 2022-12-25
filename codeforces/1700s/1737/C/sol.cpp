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

bool solve() {
  int N; cin >> N;
  int X[3], Y[3];
  bool f[2][2]; memset(f, 0, sizeof f);
  F0R(i, 3) {
    cin >> X[i] >> Y[i];
    f[X[i]&1][Y[i]&1] = 1;
  }

  auto adj = [&](int i, int j) {
    return X[i] == X[j] || Y[i] == Y[j];
  };

  int x, y; cin >> x >> y;

  bool c1 = false, c2 = false, c3 = false, c4 = false;
  F0R(i, 3) {
    int j = 0; while (j == i) j++;
    int k = 3 - i - j;
    if (X[i] == 1 && Y[i] == 1 && adj(i, j) && adj(i, k)) c1 = true;
    if (X[i] == 1 && Y[i] == N && adj(i, j) && adj(i, k)) c2 = true;
    if (X[i] == N && Y[i] == 1 && adj(i, j) && adj(i, k)) c3 = true;
    if (X[i] == N && Y[i] == N && adj(i, j) && adj(i, k)) c4 = true;
  }
  if (c1) return x == 1 || y == 1;
  if (c2) return x == 1 || y == N;
  if (c3) return x == N || y == 1;
  if (c4) return x == N || y == N;

  x &= 1; y &=1;
  return f[x][y];
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << (solve() ? "YES": "NO") << '\n';
  }
}
