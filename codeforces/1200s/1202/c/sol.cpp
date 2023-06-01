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

map<char,int> dx = {
{'W',0},
{'A',-1},
{'S',0},
{'D',1},
};

map<char,int> dy = {
{'W',1},
{'A',0},
{'S',-1},
{'D',0},
};

int G(vector<int> v) {
  vector<int> p(sz(v));
  FOR(i, 1, sz(v)) p[i] = p[i-1] + v[i];
  int MN = *min_element(all(p));
  int MX = *max_element(all(p));
  return MX-MN+1;
}

int F(vector<int> v) {
  vector<int> p(sz(v));
  FOR(i, 1, sz(v)) p[i] = p[i-1] + v[i];
  int mn = *min_element(all(p));
  int i = 0;
  while (p[i] != mn) i++;
  int MN = min(*min_element(p.begin(), p.begin()+i),
               *min_element(p.begin()+i, p.end())+1);
  int MX = max(*max_element(p.begin(), p.begin()+i),
               *max_element(p.begin()+i, p.end())+1);
  return MX-MN+1;
}

void solve() {
  string s; cin >> s;
  vector<int> v(sz(s)+1);
  F0R(i, sz(s)) v[i+1] = dx[s[i]];
  int x0 = G(v), x1 = F(v);
  F0R(i, sz(s)) v[i+1] *= -1;
  ckmin(x1, F(v));

  F0R(i, sz(s)) v[i+1] = dy[s[i]];
  int y0 = G(v), y1 = F(v);
  F0R(i, sz(s)) v[i+1] *= -1;
  ckmin(y1, F(v));

  ll ans = min(1LL * x0 * max(2, y1), 1LL * max(2, x1) * y0);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
