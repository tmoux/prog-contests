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

struct segment {
  int x1, y1, x2, y2;
  segment(int _x1, int _y1, int _x2, int _y2) {
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
  }
  segment(array<int, 2> a, array<int, 2> b) {
    x1 = a[0];
    y1 = a[1];
    x2 = b[0];
    y2 = b[1];
  }

  bool operator<(const segment &rhs) const { return false; }
};

ll len(vector<segment> v) {
  ll r = 0;
  for (auto s : v) {
    r += (ll)abs(s.x1 - s.x2) + (ll)abs(s.y1 - s.y2);
  }
  return r;
}

vector<segment> between(array<int, 2> a, array<int, 2> b) {
  if (a[0] == b[0] || a[1] == b[1]) {
    return {segment(a, b)};
  } else {
    array<int, 2> c = {a[0], b[1]};
    return {segment(a, c), segment(c, b)};
  }
}

pair<ll, vector<segment>> f(array<int, 2> a, array<int, 2> b, array<int, 2> c) {
  vector<segment> v;
  for (auto s : between(a, b)) v.push_back(s);
  for (auto s : between(a, c)) v.push_back(s);
  return {len(v), v};
}

vector<vector<segment>> h(array<int, 2> a, array<int, 2> b, array<int, 2> c) {
  vector<vector<segment>> ret;
  vector<array<int, 2>> ds = {{a[0], c[1]}, {c[0], a[1]}};
  if (a[0] <= b[0] && b[0] <= c[0]) {
    for (auto d : ds) {
      ret.push_back(
          {segment(a, d), segment(d, c), segment(b[0], b[1], b[0], d[1])});
    }
  }
  if (a[1] <= b[1] && b[1] <= c[1]) {
    for (auto d : ds) {
      ret.push_back(
          {segment(a, d), segment(d, c), segment(b[0], b[1], d[0], b[1])});
    }
  }
  return ret;
}

pair<ll, vector<segment>> g(array<int, 2> a, array<int, 2> b, array<int, 2> c) {
  pair<ll, vector<segment>> ret = {1e18, {}};
  for (auto v : h(a, b, c)) {
    ckmin(ret, {len(v), v});
  }
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  array<int, 2> a, b, c;
  cin >> a[0] >> a[1];
  cin >> b[0] >> b[1];
  cin >> c[0] >> c[1];

  pair<ll, vector<segment>> ans = {1e18, {}};
  vector<array<int, 2>> v = {a, b, c};
  sort(all(v));
  do {
    ckmin(ans, f(v[0], v[1], v[2]));
    ckmin(ans, g(v[0], v[1], v[2]));
  } while (next_permutation(all(v)));

  vector<segment> r;
  for (auto s : ans.second) {
    if (s.x1 != s.x2 || s.y1 != s.y2) {
      r.push_back(s);
    }
  }
  cout << sz(r) << endl;
  for (auto s : r) {
    cout << s.x1 << ' ' << s.y1 << ' ' << s.x2 << ' ' << s.y2 << endl;
  }
}

