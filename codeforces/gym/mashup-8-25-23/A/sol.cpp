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

namespace ModInt {
  template<int MOD>
  struct mod_int {
    int val;

    operator int() const { return val; }
    mod_int() : val(0) {}
    mod_int(ll _val) : val((_val + MOD) % MOD) {}

    mod_int operator+() const {
      return mod_int(val);
    }
    mod_int operator-() const {
      return mod_int(MOD-val);
    }
    mod_int inverse() const {
      assert(val != 0);
      return *this ^ (MOD - 2);
    }

    mod_int& operator+=(const mod_int& b) {
      val += b.val;
      if (val >= MOD) val -= MOD;
      return *this;
    }
    mod_int& operator-=(const mod_int& b) {
      return *this += -b;
    }
    mod_int& operator*=(const mod_int& b) {
      val = (1LL*val*b.val) % MOD;
      return *this;
    }
    mod_int& operator/=(const mod_int& b) {
      val = (1LL*val*b.inverse().val) % MOD;
      return *this;
    }

    mod_int& operator+=(int b) {
      return *this += mod_int(b);
    }
    mod_int& operator-=(int b) {
      return *this -= mod_int(b);
    }
    mod_int& operator*=(int b) {
      return *this *= mod_int(b);
    }
    mod_int& operator/=(int b) {
      return *this /= mod_int(b);
    }

    friend mod_int operator+(const mod_int& a, const mod_int& b) {
      mod_int c = a; c += b;
      return c;
    }
    friend mod_int operator-(const mod_int& a, const mod_int& b) {
      mod_int c = a; c -= b;
      return c;
    }
    friend mod_int operator*(const mod_int& a, const mod_int& b) {
      mod_int c = a; c *= b;
      return c;
    }
    friend mod_int operator/(const mod_int& a, const mod_int& b) {
      mod_int c = a; c /= b;
      return c;
    }

    friend mod_int operator+(const mod_int& a, int b) {
      return a + mod_int(b);
    }
    friend mod_int operator-(const mod_int& a, int b) {
      return a - mod_int(b);
    }
    friend mod_int operator*(const mod_int& a, int b) {
      return a * mod_int(b);
    }
    friend mod_int operator/(const mod_int& a, int b) {
      return a / mod_int(b);
    }
    friend mod_int operator+(int a, const mod_int& b) {
      return mod_int(a) + b;
    }
    friend mod_int operator-(int a, const mod_int& b) {
      return mod_int(a) - b;
    }
    friend mod_int operator*(int a, const mod_int& b) {
      return mod_int(a) * b;
    }
    friend mod_int operator/(int a, const mod_int& b) {
      return mod_int(a) / b;
    }

    friend mod_int operator^(mod_int a, int b) {
      mod_int res(1);
      while (b > 0) {
        if (b&1) res *= a;
        a *= a;
        b >>= 1;
      }
      return res;
    }

    friend ostream& operator<<(ostream& o, const mod_int& x) {
      return o << x.val;
    };
    friend istream& operator>>(istream& i, mod_int& x) {
      return i >> x.val;
    }
  };
}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

namespace ModCombinatorics {
  vector<int> inv, _fac, _ifac;
  template<size_t N, int MOD>
  void init() {
    inv.resize(N);
    _fac.resize(N);
    _ifac.resize(N);
    inv[0] = inv[1] = 1;
    for (size_t i = 2; i < N; i++) {
      inv[i] = (MOD - (1LL * (MOD/i) * inv[MOD%i]) % MOD) % MOD;
    }
    _fac[0] = _ifac[0] = 1;
    for (size_t i = 1; i < N; i++) {
      _fac[i] = (1LL * i * _fac[i-1]) % MOD;
      _ifac[i] = (1LL * _ifac[i-1] * inv[i]) % MOD;
    }
  }

  mint choose(int n, int k) {
    if (n < k || k < 0) return 0;
    return mint(1) * _fac[n] * _ifac[k] * _ifac[n-k];
  }

  mint fac(int n) {
    return mint(_fac[n]);
  }

  mint ifac(int n) {
    return mint(_ifac[n]);
  }

  mint strong_compositions(int n, int k) {
    if (n == 0) return k == 0 ? mint(1) : mint(0);
    return choose(n-1, k-1);
  }

  mint weak_compositions(int n, int k) {
    if (n == 0) return k == 0 ? mint(1) : mint(0);
    return choose(n+k-1, k-1);
  }
};
namespace MC = ModCombinatorics;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int maxn = 1e5+5;
  MC::init<maxn, MOD>();
  int Q; cin >> Q;
  string s; cin >> s;
  int n = sz(s);

  vector<mint> pow25(maxn), pow26(maxn), ipow26(maxn);
  pow25[0] = 1;
  FOR(i, 1, maxn) pow25[i] = 25 * pow25[i-1];
  pow26[0] = 1;
  FOR(i, 1, maxn) pow26[i] = 26 * pow26[i-1];
  ipow26[0] = 1;
  const mint inv = mint(26).inverse();
  FOR(i, 1, maxn) ipow26[i] = inv * ipow26[i-1];
  vector<mint> pfx(maxn);

  auto prep = [&](int n) {
    for (int i = 0; i < n; i++) pfx[i] = 0;
    for (int i = n; i < maxn; i++) {
      pfx[i] = MC::choose(i-1, n-1) * pow25[i-n] * ipow26[i];
      pfx[i] += pfx[i-1];
    }
  };
  prep(n);
  REP(Q) {
    int t; cin >> t;
    if (t == 1) {
      cin >> s;
      n = sz(s);
      prep(n);
    }
    else {
      int m; cin >> m;
      cout << pow26[m] * pfx[m] << '\n';
    }
  }
}
