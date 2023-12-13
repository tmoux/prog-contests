#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
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

/**
 * template name: MontgomeryModInt
 * author: Misuki
 * reference: https://github.com/NyaanNyaan/library/blob/master/modint/montgomery-modint.hpp#L10
 * last update: 2023/11/30
 * note: mod should be a prime less than 2^30.
 */

template<uint32_t mod>
struct MontgomeryModInt {
  using mint = MontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 res = 1, base = mod;
    for(i32 i = 0; i < 31; i++)
      res *= base, base *= base;
    return -res;
  }

  static constexpr u32 get_mod() {
    return mod;
  }

  static constexpr u32 n2 = -u64(mod) % mod; //2^64 % mod
  static constexpr u32 r = get_r(); //-P^{-1} % 2^32

  u32 a;

  static u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * r) * mod) >> 32;
  }

  static u32 transform(const u64 &b) {
    return reduce(u64(b) * n2);
  }

  MontgomeryModInt() : a(0) {}
  MontgomeryModInt(const int64_t &b)
    : a(transform(b % mod + mod)) {}

  mint pow(u64 k) const {
    mint res(1), base(*this);
    while(k) {
      if (k & 1)
        res *= base;
      base *= base, k >>= 1;
    }
    return res;
  }

  mint inverse() const { return (*this).pow(mod - 2); }

  u32 get() const {
    u32 res = reduce(a);
    return res >= mod ? res - mod : res;
  }

  mint& operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  mint& operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  mint& operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  mint& operator/=(const mint &b) {
    a = reduce(u64(a) * b.inverse().a);
    return *this;
  }

  mint operator-() { return mint() - mint(*this); }
  bool operator==(mint b) {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  bool operator!=(mint b) {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }

  friend mint operator+(mint a, mint b) { return a += b; }
  friend mint operator-(mint a, mint b) { return a -= b; }
  friend mint operator*(mint a, mint b) { return a *= b; }
  friend mint operator/(mint a, mint b) { return a /= b; }

  friend ostream& operator<<(ostream& os, const mint& b) {
    return os << b.get();
  }
  friend istream& operator>>(istream& is, mint& b) {
    int64_t val;
    is >> val;
    b = mint(val);
    return is;
  }
};

using mint = MontgomeryModInt<1000000007>;

/**
 * template name: NTT
 * reference: https://judge.yosupo.jp/submission/69896
 * last update: 2023/12/04
 * remark: MOD = 2^K * C + 1, R is a primitive root modulo MOD
 * remark: a.size() <= 2^K must be satisfied
 * some common modulo: 998244353  = 2^23 * 119 + 1, R = 3
 *                     469762049  = 2^26 * 7   + 1, R = 3
 *                     1224736769 = 2^24 * 73  + 1, R = 3
 * verify: Library Checker - Convolution
 */

int bit_ceil(int x)
{
  return 1 << (32 - __builtin_clz(x));
}

template<int32_t k, int32_t c, int32_t r, class Mint>
struct NTT {

  using u32 = uint32_t;
  static constexpr u32 mod = (1 << k) * c + 1;
  static constexpr u32 get_mod() { return mod; }

  static void ntt(vector<Mint> &a, bool inverse) {
    static array<Mint, 30> w, w_inv;
    if (w[0] == 0) {
      Mint root = 2;
      while(root.pow((mod - 1) / 2) == 1) root += 1;
      for(int i = 0; i < 30; i++)
        w[i] = -(root.pow((mod - 1) >> (i + 2))), w_inv[i] = 1 / w[i];
    }
    int n = sz(a);
    if (not inverse) {
      for(int m = n; m >>= 1; ) {
        Mint ww = 1;
        for(int s = 0, l = 0; s < n; s += 2 * m) {
          for(int i = s, j = s + m; i < s + m; i++, j++) {
            Mint x = a[i], y = a[j] * ww;
            a[i] = x + y, a[j] = x - y;
          }
          ww *= w[__builtin_ctz(++l)];
        }
      }
    } else {
      for(int m = 1; m < n; m *= 2) {
        Mint ww = 1;
        for(int s = 0, l = 0; s < n; s += 2 * m) {
          for(int i = s, j = s + m; i < s + m; i++, j++) {
            Mint x = a[i], y = a[j];
            a[i] = x + y, a[j] = (x - y) * ww;
          }
          ww *= w_inv[__builtin_ctz(++l)];
        }
      }
      Mint inv = 1 / Mint(n);
      for(Mint &x : a) x *= inv;
    }
  }

  vector<Mint> conv(vector<Mint> a, vector<Mint> b) {
    int sz = sz(a) + sz(b) - 1;
    int n = bit_ceil((u32)sz);

    a.resize(n, 0);
    ntt(a, false);
    b.resize(n, 0);
    ntt(b, false);

    for(int i = 0; i < n; i++)
      a[i] *= b[i];

    ntt(a, true);

    a.resize(sz);

    return a;
  }
};

/**
 * template name: NTTanyMod
 * author: Misuki
 * last update: 2023/12/04
 * reference: https://math314.hateblo.jp/entry/2015/05/07/014908
 *            https://judge.yosupo.jp/submission/15581
 * remark: n * mod^2 < prod of mods(~= 5e26) should be satisfied
 * some common modulo: 998244353  = 2^23 * 119 + 1, R = 3
 *                     469762049  = 2^26 * 7   + 1, R = 3
 *                     167772161  = 2^25 * 5   + 1, R = 3
 * verify: Library Checker - Convolution (Mod 1,000,000,007)
 */

template<class Mint>
vector<Mint> convAnyMod(vector<Mint> a, vector<Mint> b) {
  using Mint0 = MontgomeryModInt<998244353>;
  using Mint1 = MontgomeryModInt<469762049>;
  using Mint2 = MontgomeryModInt<167772161>;
  NTT<23, 119, 3, Mint0> ntt0;
  NTT<26, 7, 3, Mint1> ntt1;
  NTT<25, 5, 3, Mint2> ntt2;
  vector<Mint0> a0(sz(a)), b0(sz(b));
  vector<Mint1> a1(sz(a)), b1(sz(b));
  vector<Mint2> a2(sz(a)), b2(sz(b));
  for(int i = 0; i < sz(a); i++)
    a0[i] = a[i].get(), a1[i] = a[i].get(), a2[i] = a[i].get();
  for(int i = 0; i < sz(b); i++)
    b0[i] = b[i].get(), b1[i] = b[i].get(), b2[i] = b[i].get();
  vector<Mint0> x = ntt0.conv(a0, b0);
  vector<Mint1> y = ntt1.conv(a1, b1);
  vector<Mint2> z = ntt2.conv(a2, b2);
  vector<Mint> res(sz(x));
  constexpr uint32_t mod0 = ntt0.get_mod(), mod1 = ntt1.get_mod();
  static const Mint1 im0 = 1 / Mint1(mod0);
  static const Mint2 im1 = 1 / Mint2(mod1), im0m1 = im1 / mod0;
  static const Mint m0 = mod0, m0m1 = m0 * mod1;
  for(int i = 0; i < sz(x); i++) {
    int y0 = x[i].get();
    int y1 = (im0 * (y[i] - y0)).get();
    int y2 = (im0m1 * (z[i] - y0) - im1 * y1).get();
    res[i] = y0 + m0 * y1 + m0m1 * y2;
  }

  return res;
}

mint solve() {
  int N; cin >> N;
  vector<vector<int>> adj(N);
  REP(N-1) {
    int a, b; cin >> a >> b; a--, b--;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  auto ans = y_combinator([&](auto dfs, int i, int p) -> vector<mint> {
    vector<vector<mint>> ch;
    ch.reserve(sz(adj[i]));
    ch.push_back({1, 0, 1});
    for (int j: adj[i]) {
      if (j == p) continue;
      auto v = dfs(j, i);
      ch.push_back(v);
    }
    auto prod = y_combinator([&](auto f, int l, int r) -> vector<mint> {
      if (l > r) return {1};
      if (l == r) return ch[l];
      int m = (l + r) / 2;
      return convAnyMod<mint>(f(l, m), f(m+1, r));
    })(0, sz(ch) - 1);

    int s = sz(ch);
    return {prod[s-1], prod[s], prod[s+1]};
  })(0, 0);

  mint total = 0;
  for (auto x: ans) total += x;
  return total;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) cout << solve() << '\n';
}
