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

int get_tm_val(ll x) {
  return __builtin_popcountll(x) & 1;
}

int dist(ll i, ll d) {
  return get_tm_val(d-1) != get_tm_val(i+d-1);
}

map<pair<ll, ll>, ll> dp;

ll f(ll i, ll d) {
  if (dp.count({i, d})) return dp[{i, d}];
  if (d == 0) return 0;
  else if (d == 1) return dist(i, d);
  ll ans = 0;
  if (i % 2 == 0) {
    ans = 2 * f(i/2, d/2) + (d&1 ? dist(i, d) : 0);
  }
  else {
    if (d % 2 == 1) {
      ans += d/2+1 - f(i/2, d/2+1);
      ans += d/2   - f(i/2+1, d/2);
    }
    else {
      ans += d/2 - f(i/2, d/2);
      ans += d/2 - f(i/2+1, d/2);
    }
  }
  return dp[{i, d}] = ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    ll N, M; cin >> N >> M;
    cout << f(N, M) << '\n';
  }
}
