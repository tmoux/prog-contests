#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

ll solve() {
  int n; cin >> n;
  vector<ll> h(n);
  F0R(i, n) cin >> h[i];

  auto f = [](ll A, ll B) -> ll {
    if (A > B) return 2 * A - 1;
    else return 2 * B;
  };

  auto calc = [&](vector<ll> v, int b) -> ll {
    ll mx = 0;
    ll A = 0, B = 0;
    F0R(i, n) {
      if (v[i] % 2 == b) {
        v[i]++;
        A++;
      }
      ckmax(mx, v[i]);
    }
    F0R(i, n) {
      B += (mx - v[i]) / 2;
    }
    // cout << v << endl;
    // cout << A << ' ' << B << endl;
    ll x = (B - A) / 3;

    ll ans = f(A, B);
    for (ll y = max(0LL, x-20); y <= x + 20; y++) {
      if (B - y >= 0) {
        ckmin(ans, f(A + 2*y, B - y));
      }
    }
    // cout << ": " << ans << endl;
    return ans;
  };

  ll ans = min(calc(h, 0), calc(h, 1));
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  REP(T) cout << solve() << '\n';
}
