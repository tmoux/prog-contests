#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using ld = long double;

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

void solve() {
  int n; cin >> n;

  ll minL = 2e9, maxR = -2e9;
  ll lcost = 2e9, rcost = 2e9;

  pair<ll,ll> both = {-1, -1};
  ll bothcost = 2e9;
  F0R(i, n) {
    ll l, r, c; cin >> l >> r >> c;


    if (l < minL) {
      minL = l;
      lcost = c;
    }
    else if (l == minL) ckmin(lcost, c);

    if (r > maxR) {
      maxR = r;
      rcost = c;
    }
    else if (r == maxR) ckmin(rcost, c);

    if (both != make_pair(minL, maxR)) {
      both = {-1, -1};
      bothcost = 2e9;
    }
    if (l == minL && r == maxR && c < bothcost) {
      bothcost = c;
      both = {l, r};
    }

    //cout << "as " << minL << ' ' << maxR << endl;
    //cout << lcost << ' ' << rcost << ' ' << bothcost << endl;

    ll ans = lcost + rcost;
    if (both == make_pair(minL, maxR))
        ckmin(ans, bothcost);

    cout << ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
