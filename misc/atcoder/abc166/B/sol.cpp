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

/*
** ABC
** AB C
** AC B
** BC A
** A B C
 */

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  ll A, B, C; cin >> A >> B >> C;
  vector<ll> X(N);
  F0R(i, N) cin >> X[i];

  auto calc = [&](ll x, ll m) -> ll {
    return x % m == 0 ? 0 : m - (x % m);
  };

  ll ans = -1;
  // ABC
  F0R(i, N) {
    if (i == 0) ans = calc(X[i], lcm(lcm(A, B), C));
    else ckmin(ans, calc(X[i], lcm(lcm(A, B), C)));
  }

  vector<pair<ll, int>> AS, BS;
  auto prep = [&](ll a, ll b) {
    AS.clear(); BS.clear();
    F0R(i, N) {
      AS.emplace_back(calc(X[i], a), i);
      BS.emplace_back(calc(X[i], b), i);
    }
    sort(all(AS));
    sort(all(BS));
  };
  auto solve2 = [&](int exclude, ll a, ll b) -> ll {
    const ll INF = 1e18 + 5;
    ll ans = 2 * INF;
    F0R(i, min(5, sz(AS))) {
      F0R(j, min(5, sz(BS))) {
        if (AS[i].second != BS[j].second && AS[i].second != exclude && BS[j].second != exclude) {
          ckmin(ans, AS[i].first + BS[j].first);
        }
      }
    }
    return ans;
  };

  prep(lcm(A, B), C);
  ckmin(ans, solve2(-1, lcm(A, B), C));
  prep(lcm(A, C), B);
  ckmin(ans, solve2(-1, lcm(A, C), B));
  prep(lcm(B, C), A);
  ckmin(ans, solve2(-1, lcm(B, C), A));

  prep(B, C);
  F0R(i, N) {
    ckmin(ans, calc(X[i], A) + solve2(i, B, C));
  }

  cout << ans << '\n';
}
