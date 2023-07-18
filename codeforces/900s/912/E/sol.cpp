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



vector<int> p;

const double INF = 1e18 + 10;
vector<ll> vs;
void rec(int i, ll prod, bool f) {
  if (f) vs.push_back(prod);
  if (i >= sz(p)) {
    return;
  }
  rec(i+1, prod, 0);
  ll np = prod;
  while (np <= INF) {
    if ((double)np * p[i] <= INF) {
      np *= p[i];
      rec(i+1, np, 1);
    }
    else break;
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  vector<int> p1, p2;
  vector<int> primes(N);
  F0R(i, N) cin >> primes[i];
  ll K; cin >> K;
  shuffle(all(primes), rng);
  F0R(i, N) {
    (i % 2 == 0 ? p1 : p2).push_back(primes[i]);
  }

  p = p1;
  rec(0, 1, 1);
  vector<ll> v1 = vs; vs.clear();

  p = p2;
  rec(0, 1, 1);
  vector<ll> v2 = vs; vs.clear();

  sort(all(v1));
  sort(all(v2));

  auto mult = [](ll a, ll b) -> ll {
    if ((double)a * b >= INF) return INF;
    return a * b;
  };

  auto check = [&](ll x) -> ll {
    ll res = 0;
    int j = sz(v2) - 1;
    for (int i = 0; i < sz(v1); i++) {
      while (j >= 0 && mult(v1[i], v2[j]) > x) j--;
      res += j+1;
    }
    return res;
  };

  ll lo = 0, hi = 1e18 + 10;
  while (lo + 1 < hi) {
    ll mid = std::midpoint(lo, hi);
    (check(mid) < K ? lo : hi) = mid;
  }
  cout << hi << '\n';
}
