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
const int MOD = 1e9+7;;
using mint = ModInt::mod_int<MOD>;

namespace atcoder {
  // @param n 0
  // @return minimum non-negative Symbol’s value as variable is void: x s.t. Symbol’s value as variable is void: n
  int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
  }

  template <class S, S (*op)(S, S), S (*e)()> struct segtree {
    public:
      segtree() : segtree(0) {}
      explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
      explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
          update(i);
        }
      }

      void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
      }

      S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
      }

      S prod(int l, int r) const {
        r++; // make range [l, r] inclusive.
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
          if (l & 1) sml = op(sml, d[l++]);
          if (r & 1) smr = op(d[--r], smr);
          l >>= 1;
          r >>= 1;
        }
        return op(sml, smr);
      }

      S all_prod() const { return d[1]; }

      template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
      }
      template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
          while (l % 2 == 0) l >>= 1;
          if (!f(op(sm, d[l]))) {
            while (l < size) {
              l = (2 * l);
              if (f(op(sm, d[l]))) {
                sm = op(sm, d[l]);
                l++;
              }
            }
            return l - size;
          }
          sm = op(sm, d[l]);
          l++;
        } while ((l & -l) != l);
        return _n;
      }

      template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
      }
      template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
          r--;
          while (r > 1 && (r % 2)) r >>= 1;
          if (!f(op(d[r], sm))) {
            while (r < size) {
              r = (2 * r + 1);
              if (f(op(d[r], sm))) {
                sm = op(d[r], sm);
                r--;
              }
            }
            return r + 1 - size;
          }
          sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
      }

    private:
      int _n, size, log;
      std::vector<S> d;

      void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
  };
} // namespace atcoder
using atcoder::segtree;

namespace Seg {
  using T = mint;
  T op(T a, T b) { return a + b; }

  T e() { return 0; }
}

void solve() {
  int N; cin >> N;
  vector<int> X(N), W(N);
  F0R(i, N) cin >> X[i];
  F0R(i, N) cin >> W[i];

  mint ans = 0;
  REP(2) {
    segtree<Seg::T, Seg::op, Seg::e> seg1(N+1), seg2(N+1);
    F0R(j, N) {
      mint add1 = X[j] / (mint(2) ^ (W[j] + 1)) * seg1.prod(0, W[j]);
      mint add2 = (1 / (mint(2) ^ (W[j] + 1))) * seg2.prod(0, W[j]);
      ans += add1 - add2;

      seg1.set(W[j], mint(2) ^ W[j]);
      seg2.set(W[j], X[j] * (mint(2) ^ W[j]));
    }

    F0R(j, N) {
      W[j] = N + 1 - W[j];
    }
  }

  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
