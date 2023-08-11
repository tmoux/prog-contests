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

int n, k;
string s;

pair<int, string> mx = {0, ""};
pair<int, string> mn = {99999, ""};

map<int, int> mp;
int count(string s) {
  set<string> vs;
  F0R(i, sz(s)) {
    for (int j = 1; i + j <= sz(s); j++) {
      string t = s.substr(i, j);
      string u = t; reverse(all(u));
      if (t == u) vs.insert(t);
    }
  }
  return sz(vs);
}

void rec(int i) {
  if (i == n) {
    int x = count(s);
    ckmax(mx, {x, s});
    ckmin(mn, {x, s});
    mp[x]++;
    cout << s << ": " << x << endl;
    return;
  }

  F0R(j, k) {
    s += 'a' + j;
    rec(i+1);
    s.pop_back();
  }
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  while (true) {
    string s; cin >> s;
    cout << s << ": " << count(s) << endl;
  }
  cin >> n >> k;
  rec(0);
  cout << mx << endl;
  cout << mn << endl;
  cout << mp << endl;
}
