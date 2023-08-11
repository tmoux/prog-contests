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
  int n; cin >> n;
  vector<ll> a(n);
  F0R(i, n) cin >> a[i];
  int ans = 1;
  auto issqr = [](ll x) -> bool {
    ll s = max(0LL, (ll)sqrt(x) - 3);
    while (1LL * (s+1)*(s+1) <= x) s++;
    return s*s == x;
  };

  F0R(i, n) {
    FOR(j, i+1, n) {
      // cout << i << ' ' << j << endl;
      ll diff = a[j] - a[i];
      for (ll d = 1; d*d <= diff; d++) {
        // cout << d << endl;
        if (diff % d == 0) {
          ll A = d, B = diff / d;
          if ((A + B) % 2 == 0) {
            ll x = (B - A) / 2, y = (A + B) / 2;
            if (a[i] <= x * x && a[j] <= y*y) {
              ll k = x * x - a[i];
              assert(k == y*y-a[j]);
              int cnt = 0;
              for (int idx = 0; idx < n; idx++) {
                if (issqr(a[idx] + k)) cnt++;
              }
              ckmax(ans, cnt);
            }
          }
        }
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
