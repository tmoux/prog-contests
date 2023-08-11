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
// }}}

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

      constexpr mod_int() : val(0) {}
      constexpr mod_int(int _val) : val(_val % MOD) {}

      constexpr mod_int operator+() const {
        return mod_int(val); 
      }
      constexpr mod_int operator-() const {
        return mod_int(MOD-val); 
      }
      constexpr mod_int inverse() const {
        assert(val != 0);
        return *this ^ (MOD - 2);
      }

      constexpr mod_int& operator+=(const mod_int& b) {
        val += b.val;
        if (val >= MOD) val -= MOD;
        return *this;
      }
      constexpr mod_int& operator-=(const mod_int& b) {
        return *this += -b;
      }
      constexpr mod_int& operator*=(const mod_int& b) {
        val = (1LL*val*b.val) % MOD;
        return *this;
      }
      constexpr mod_int& operator/=(const mod_int& b) {
        val = (1LL*val*b.inverse().val) % MOD;
        return *this;
      }

      constexpr mod_int& operator+=(int b) {
        return *this += mod_int(b);
      }
      constexpr mod_int& operator-=(int b) {
        return *this -= mod_int(b);
      }
      constexpr mod_int& operator*=(int b) {
        return *this *= mod_int(b);
      }
      constexpr mod_int& operator/=(int b) {
        return *this /= mod_int(b);
      }

      constexpr friend mod_int operator+(const mod_int& a, const mod_int& b) {
        mod_int c = a; c += b;
        return c;
      }
      constexpr friend mod_int operator-(const mod_int& a, const mod_int& b) {
        mod_int c = a; c -= b;
        return c;
      }
      constexpr friend mod_int operator*(const mod_int& a, const mod_int& b) {
        mod_int c = a; c *= b;
        return c;
      }
      constexpr friend mod_int operator/(const mod_int& a, const mod_int& b) {
        mod_int c = a; c /= b;
        return c;
      }

      constexpr friend mod_int operator^(mod_int a, int b) {
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
        i >> x.val; x.val %= MOD;
        return i;
      }
    };

} //}}}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

template<size_t N, int MOD>
struct ModCombinatorics {
  int *inv, *fac, *ifac;
  ModCombinatorics() {
    inv = new int[N];
    fac = new int[N];
    ifac = new int[N];
    inv[0] = inv[1] = 1;
    for (size_t i = 2; i < N; i++) {
      inv[i] = (MOD - (1LL * (MOD/i) * inv[MOD%i]) % MOD) % MOD;
    }
    fac[0] = ifac[0] = 1;
    for (size_t i = 1; i < N; i++) {
      fac[i] = (1LL * i * fac[i-1]) % MOD;
      ifac[i] = (1LL * ifac[i-1] * inv[i]) % MOD;
    }
  }
  constexpr int choose(int n, int k) const {
    return (1LL * fac[n] * ((1LL * ifac[k] * ifac[n-k]) % MOD)) % MOD;
  }

  ~ModCombinatorics() {
    delete[] inv; 
    delete[] fac; 
    delete[] ifac;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int maxn = 2e5+5;
  ModCombinatorics<maxn, MOD> MC;

  int n; cin >> n;
  int B = 0, W = 0;
  vector<string> s(n);
  F0R(i, n) {
    cin >> s[i];
    for (char c: s[i]) {
      if (c == 'B') B++;
      else if (c == 'W') W++;
    }
  }
  if (B <= n && W <= n) {
    mint total = MC.choose(2*n-B-W, n-W);
    mint sub = 1;
    for (auto t: s) {
      if (t == "??") sub *= 2;
      else if (t == "BB" || t == "WW") sub = 0;
    }
    total -= sub;

    bool allBW = true;
    for (auto t: s) {
      if (t != "??" && t != "?W" && t != "B?" && t != "BW") 
        allBW = false;
    }
    if (allBW) total += 1;

    bool allWB = true;
    for (auto t: s) {
      if (t != "??" && t != "?B" && t != "W?" && t != "WB") 
        allWB = false;
    }
    if (allWB) total += 1;
    cout << total << '\n';
  }
  else {
    cout << 0 << '\n';
  }
}
