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

ll ceil(ll a, ll b) {
  return (a + b - 1) / b;
}

ll solve() {
  ll a, b, c, d; cin >> a >> b >> c >> d;
  auto eval = [&](ll t) -> ll {
    ll ans = -a * (t + 1);
    ans += ((d * t - c) / d + 1) * b * c;
    ll s = c % d == 0 ? c / d - 1 : c / d;
    ans += s * (s + 1) / 2 * b * d;
    return ans;
  };
  auto evalSmall = [&](ll t) -> ll {
    ll ans = -a * (t + 1);
    ans += b * d * (t * (t + 1) / 2);
    return ans;
  };
  //Case 1: c <= d:
  if (c <= d) {
    if (b * c - a < 0) return -1;
    else return a;
  }
  else {
    // Case 2: c > d:
    if (b * c - a < 0) return -1;
    else {
      ll t = ceil(c, d);
      ll t2 = c % d == 0 ? c / d - 1 : c / d;
      ll ans = a;
      ckmax(ans, max(-eval(t), -evalSmall(t2)));
      ll t3 = -(b * d / 2 - a) / (b * d);
      for (ll x = max(0LL, t3-10); x <= min(t2, t3+10); x++) {
        ckmax(ans, -evalSmall(x));
      }
      return ans;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
