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

typedef unsigned long long ull;
struct FastMod {
  ull b, m;
  FastMod(ull b) : b(b), m(-1ULL / b) {}
  ull reduce(ull a) { // a % b + (0 or b)
    return a - (ull)((__uint128_t(m) * a) >> 64) * b;
  }
};

const int maxn = 1e6+6;
int spf[maxn];

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
      for (int j = i; j < maxn; j += i) {
        if (!spf[j]) spf[j] = i;
      }
    }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  int x, q, M; cin >> x >> q >> M;
  FastMod RED(M);
  auto mult = [&](ull a, ull b) {
    return RED.reduce(a * b);
  };
  auto modexp = [&](ull a, ull k) {
    ull res = 1;
    while (k > 0) {
      if (k&1) res = mult(res, a);
      a = mult(a, a);
      k >>= 1;
    }
    return res;
  };
  auto inverse = [&](ull a) {
    return modexp(a, M-2);
  };

  map<int, int> mp;
  ull prod = 1;

  int zeros = 0;
  auto add = [&](int p) {
    if ((mp[p] + 2) % M == 0) {
      zeros++;
      mp[p]++;
    }
    else if ((mp[p] + 1) % M == 0) {
      zeros--;
      prod = mult(prod, inverse(mp[p]));
      mp[p]++;
    }
    else {
      prod = mult(prod, inverse(mp[p]+1));
      mp[p]++;
      prod = mult(prod, mp[p]+1);
    }
  };

  map<int, int> divs;
  int orig = x;
  for (int i = 2; i*i <= orig; i++) {
    if (x % i == 0) {
      while (x % i == 0) {
        if (i > 2) add(i);
        x /= i;
      }
    }
  }
  if (x > 2) add(x);

  REP(q) {
    int xi; cin >> xi;
    while (xi > 1) {
      int p = spf[xi];
      if (p > 2) add(p);
      xi /= p;
    }
    ull ans = zeros > 0 ? 0 : prod % M;
    cout << ans << '\n';
  }
}
