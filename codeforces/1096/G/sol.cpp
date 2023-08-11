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


namespace ModInt { //{{{
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
} //}}}

// Based on https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/NumberTheoreticTransform.h
const int mod = (119 << 23) + 1, root = 62; // = 998244353
using mint = ModInt::mod_int<mod>;

template<typename T, unsigned ROOT>
struct NTT {
  void ntt(vector<T> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vector<T> rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
      rt.resize(n);
      T z[] = {1, T(root) ^ (mod >> s)};
      FOR(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1];
    }
    vector<int> rev(n);
    FOR(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    FOR(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
      for (int i = 0; i < n; i += 2 * k) FOR(j,0,k) {
          mint z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
          a[i + j + k] = ai - z;
          ai += z;
        }
  }
  vector<T> conv(const vector<T> &a, const vector<T> &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    mint inv = 1 / mint(n);
    vector<T> L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    FOR(i,0,n) out[-i & (n - 1)] = L[i] * R[i] * inv;
    ntt(out);
    return {out.begin(), out.begin() + s};
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, K; cin >> N >> K;
  vector<mint> p(10);
  REP(K) {
    int d; cin >> d;
    p[d] = 1;
  }
  NTT<mint, root> ntt;
  vector<mint> poly = {1};
  int n = N/2;
  while (n) {
    if (n&1) poly = ntt.conv(poly, p);
    p = ntt.conv(p, p);
    n >>= 1;
  }

  mint total = 0;
  for (auto x: poly) {
    total += x * x;
  }
  cout << total << '\n';
}
