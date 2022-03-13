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

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    int n; cin >> n;
    vector<ll> a(n), b(n);
    F0R(i, n) cin >> a[i];
    F0R(i, n) cin >> b[i];
    ll A = a.front();
    ll B = a.back();
    ll C = b.front();
    ll D = b.back();

    sort(all(a));
    sort(all(b));
    auto smallest = [](int x, const vector<ll>& v) -> ll {
      auto it = lower_bound(all(v), x);
      ll ret = 2e9;
      if (it != v.end()) ckmin(ret, *it - x);
      if (it != v.begin()) ckmin(ret, x - *prev(it));
      return ret;
    };

    ll ans = 1e18;
    ckmin(ans, abs(A - C) + abs(B - D));
    ckmin(ans, abs(A - D) + abs(B - C));

    ckmin(ans, abs(A - C) + smallest(B, b) + smallest(D, a));
    ckmin(ans, abs(A - D) + smallest(B, b) + smallest(C, a));
    ckmin(ans, abs(B - C) + smallest(A, b) + smallest(D, a));
    ckmin(ans, abs(B - D) + smallest(A, b) + smallest(C, a));

    ckmin(ans, smallest(A, b) + smallest(B, b) + smallest(C, a) + smallest(D, a));

    cout << ans << '\n';
  }
}
