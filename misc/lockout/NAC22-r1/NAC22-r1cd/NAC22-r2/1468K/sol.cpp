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

map<char, pair<int,int>> mp = {
  {'U', {0, 1}},
  {'D', {0, -1}},
  {'L', {-1, 0}},
  {'R', {1, 0}},
};

pair<int,int> block(string s, int j) {
  int x = 0, y = 0;
  int X = 0, Y = 0;
  F0R(i, sz(s)) {
    char c = s[i];
    x += mp[c].first;
    y += mp[c].second;
    if (i == j) {
      X = x;
      Y = y;
      break;
    }
  }

  x = 0, y = 0;
  F0R(i, sz(s)) {
    char c = s[i];

    int nx = x + mp[c].first;
    int ny = y + mp[c].second;

    if (nx == X && ny == Y) {
      continue;
    }
    else {
      x = nx;
      y = ny;
    }
  }
  if (x == 0 && y == 0) {
    return {X, Y};
  }
  else return {0, 0};
}

void solve() {
  string s; cin >> s;
  int x = 0, y = 0;
  for (char c: s) {
    x += mp[c].first;
    y += mp[c].second;
  }
  if (x == 0 && y == 0) {
    assert(false);
  }
  F0R(i, sz(s)) {
    auto [a, b] = block(s, i);
    if (a == 0 && b == 0) {
      continue;
    }
    else {
      cout << a << ' ' << b << endl;
      return;
    }
  }
  cout << 0 << ' ' << 0 << endl;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}

