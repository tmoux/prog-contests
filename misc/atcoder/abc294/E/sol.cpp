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
  ll L; cin >> L;
  int N1, N2;
  cin >> N1 >> N2;
  vector<pair<int, ll>> v1(N1), v2(N2);
  F0R(i, N1) {
    int v; ll l; cin >> v >> l;
    v1[i] = {v, l};
  }
  F0R(i, N2) {
    int v; ll l; cin >> v >> l;
    v2[i] = {v, l};
  }
  reverse(all(v1));
  reverse(all(v2));

  int cur = 0;
  ll extra = 0;
  int val = -1;

  ll ans = 0;
  while (true) {
    if (cur == 0) {
      // take v2
      if (v2.empty()) break;
      auto [v, l] = v2.back(); v2.pop_back();
      if (v == val) {
        ans += min(extra, l);
      }
      if (l > extra) {
        cur = 1;
        extra = l - extra;
        val = v;
      }
      else extra -= l;
    }
    else {
      // take v1
      if (v1.empty()) break;
      auto [v, l] = v1.back(); v1.pop_back();
      if (v == val) {
        ans += min(extra, l);
      }
      if (l > extra) {
        cur = 0;
        extra = l - extra;
        val = v;
      }
      else extra -= l;
    }
  }
  cout << ans << '\n';
}
