#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
#define REP(n) for (int _ = 0; _ < (n); _++)
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define FORd(i, a, b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)

#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()

template <class T>
bool ckmin(T &a, const T &b) {
  return b < a ? a = b, 1 : 0;
}
template <class T>
bool ckmax(T &a, const T &b) {
  return a < b ? a = b, 1 : 0;
}

namespace std {
template <class Fun>
class y_combinator_result {
  Fun fun_;

  public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

  template <class... Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}  // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '[';
  string sep;
  for (const T &x : v) os << sep << x, sep = ", ";
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
    mod_int(int _val) : val(_val % MOD) {}

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

namespace ModCombinatorics { // {{{
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
};
// }}}
namespace MC = ModCombinatorics;

namespace fft {
  typedef double dbl;

  struct num {
    dbl x, y;
    num() { x = y = 0; }
    num(dbl x, dbl y) : x(x), y(y) { }
  };

  inline num operator+(num a, num b) { return num(a.x + b.x, a.y + b.y); }
  inline num operator-(num a, num b) { return num(a.x - b.x, a.y - b.y); }
  inline num operator*(num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
  inline num conj(num a) { return num(a.x, -a.y); }

  int base = 1;
  vector<num> roots = {{0, 0}, {1, 0}};
  vector<int> rev = {0, 1};

  const dbl PI = acosl(-1.0);

  void ensure_base(int nbase) {
    if (nbase <= base) {
      return;
    }
    rev.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    roots.resize(1 << nbase);
    while (base < nbase) {
      dbl angle = 2 * PI / (1 << (base + 1));
//      num z(cos(angle), sin(angle));
      for (int i = 1 << (base - 1); i < (1 << base); i++) {
        roots[i << 1] = roots[i];
//        roots[(i << 1) + 1] = roots[i] * z;
        dbl angle_i = angle * (2 * i + 1 - (1 << base));
        roots[(i << 1) + 1] = num(cos(angle_i), sin(angle_i));
      }
      base++;
    }
  }

  void fft(vector<num> &a, int n = -1) {
    if (n == -1) {
      n = a.size();
    }
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; i++) {
      if (i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for (int k = 1; k < n; k <<= 1) {
      for (int i = 0; i < n; i += 2 * k) {
        for (int j = 0; j < k; j++) {
          num z = a[i + j + k] * roots[j + k];
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
      }
    }
/*    for (int len = 1; len < n; len <<= 1) {
      for (int i = 0; i < n; i += 2 * len) {
      for (int j = i, k = i + len; j < i + len; j++, k++) {
      num z = a[k] * roots[k - i];
      a[k] = a[j] - z;
      a[j] = a[j] + z;
      }
      }
      }*/
  }

  vector<num> fa, fb;

  vector<int> multiply(vector<int> &a, vector<int> &b) {
    int need = a.size() + b.size() - 1;
    int nbase = 1;
    while ((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if (sz > (int) fa.size()) {
      fa.resize(sz);
    }
    for (int i = 0; i < sz; i++) {
      int x = (i < (int) a.size() ? a[i] : 0);
      int y = (i < (int) b.size() ? b[i] : 0);
      fa[i] = num(x, y);
    }
    fft(fa, sz);
    num r(0, -0.25 / (sz >> 1));
    for (int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      num z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
      if (i != j) {
        fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
      }
      fa[i] = z;
    }
    for (int i = 0; i < (sz >> 1); i++) {
      num A0 = (fa[i] + fa[i + (sz >> 1)]) * num(0.5, 0);
      num A1 = (fa[i] - fa[i + (sz >> 1)]) * num(0.5, 0) * roots[(sz >> 1) + i];
      fa[i] = A0 + A1 * num(0, 1);
    }
    fft(fa, sz >> 1);
    vector<int> res(need);
    for (int i = 0; i < need; i++) {
      if (i % 2 == 0) {
        res[i] = fa[i >> 1].x + 0.5;
      } else {
        res[i] = fa[i >> 1].y + 0.5;
      }
    }
    return res;
  }

  vector<int> square(const vector<int> &a) {
    int need = a.size() + a.size() - 1;
    int nbase = 1;
    while ((1 << nbase) < need) nbase++;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if ((sz >> 1) > (int) fa.size()) {
      fa.resize(sz >> 1);
    }
    for (int i = 0; i < (sz >> 1); i++) {
      int x = (2 * i < (int) a.size() ? a[2 * i] : 0);
      int y = (2 * i + 1 < (int) a.size() ? a[2 * i + 1] : 0);
      fa[i] = num(x, y);
    }
    fft(fa, sz >> 1);
    num r(1.0 / (sz >> 1), 0.0);
    for (int i = 0; i <= (sz >> 2); i++) {
      int j = ((sz >> 1) - i) & ((sz >> 1) - 1);
      num fe = (fa[i] + conj(fa[j])) * num(0.5, 0);
      num fo = (fa[i] - conj(fa[j])) * num(0, -0.5);
      num aux = fe * fe + fo * fo * roots[(sz >> 1) + i] * roots[(sz >> 1) + i];
      num tmp = fe * fo;
      fa[i] = r * (conj(aux) + num(0, 2) * conj(tmp));
      fa[j] = r * (aux + num(0, 2) * tmp);
    }
    fft(fa, sz >> 1);
    vector<int> res(need);
    for (int i = 0; i < need; i++) {
      if (i % 2 == 0) {
        res[i] = fa[i >> 1].x + 0.5;
      } else {
        res[i] = fa[i >> 1].y + 0.5;
      }
    }
    return res;
  }

    vector<int> multiply_mod(vector<int> &a, vector<int> &b, int m, int eq = 0) {
      int need = a.size() + b.size() - 1;
      int nbase = 0;
      while ((1 << nbase) < need) nbase++;
      ensure_base(nbase);
      int sz = 1 << nbase;
      if (sz > (int) fa.size()) {
        fa.resize(sz);
      }
      for (int i = 0; i < (int) a.size(); i++) {
        int x = (a[i] % m + m) % m;
        fa[i] = num(x & ((1 << 15) - 1), x >> 15);
      }
      fill(fa.begin() + a.size(), fa.begin() + sz, num {0, 0});
      fft(fa, sz);
      if (sz > (int) fb.size()) {
        fb.resize(sz);
      }
      if (eq) {
        copy(fa.begin(), fa.begin() + sz, fb.begin());
      } else {
        for (int i = 0; i < (int) b.size(); i++) {
          int x = (b[i] % m + m) % m;
          fb[i] = num(x & ((1 << 15) - 1), x >> 15);
        }
        fill(fb.begin() + b.size(), fb.begin() + sz, num {0, 0});
        fft(fb, sz);
      }
      dbl ratio = 0.25 / sz;
      num r2(0, -1);
      num r3(ratio, 0);
      num r4(0, -ratio);
      num r5(0, 1);
      for (int i = 0; i <= (sz >> 1); i++) {
        int j = (sz - i) & (sz - 1);
        num a1 = (fa[i] + conj(fa[j]));
        num a2 = (fa[i] - conj(fa[j])) * r2;
        num b1 = (fb[i] + conj(fb[j])) * r3;
        num b2 = (fb[i] - conj(fb[j])) * r4;
        if (i != j) {
          num c1 = (fa[j] + conj(fa[i]));
          num c2 = (fa[j] - conj(fa[i])) * r2;
          num d1 = (fb[j] + conj(fb[i])) * r3;
          num d2 = (fb[j] - conj(fb[i])) * r4;
          fa[i] = c1 * d1 + c2 * d2 * r5;
          fb[i] = c1 * d2 + c2 * d1;
        }
        fa[j] = a1 * b1 + a2 * b2 * r5;
        fb[j] = a1 * b2 + a2 * b1;
      }
      fft(fa, sz);
      fft(fb, sz);
      vector<int> res(need);
      for (int i = 0; i < need; i++) {
        long long aa = fa[i].x + 0.5;
        long long bb = fb[i].x + 0.5;
        long long cc = fa[i].y + 0.5;
        res[i] = (aa + ((bb % m) << 15) + ((cc % m) << 30)) % m;
      }
      return res;
    }

  vector<int> square_mod(vector<int> &a, int m) {
    return multiply_mod(a, a, m, 1);
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  const int maxn = 2e5+5;
  MC::init<maxn, MOD>();
  int N, K; cin >> N >> K;

  vector<int> A(N+1), B(N+1);
  F0R(i, N+1) {
    A[i] = (mint(i&1 ? MOD-1 : 1) * MC::ifac(i)).val;
    B[i] = ((mint(i) ^ N) * MC::ifac(i)).val;
  }

  auto F = fft::multiply_mod(A, B, MOD);
  for (int k = 0; k <= K; k++) {
    cout << k << ": " << F[k] << endl;
  }

  return 0;
}
