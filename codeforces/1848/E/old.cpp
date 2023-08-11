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

int x, q, M;
FastMod RED(1);
ull mult(ull a, ull b) {
  return RED.reduce(a * b);
};
ull modexp(ull a, ull k) {
  ull res = 1;
  while (k > 0) {
    if (k&1) res = mult(res, a);
    a = mult(a, a);
    k >>= 1;
  }
  return res;
};
ull inverse(ull a) {
  return modexp(a, M-2);
};

namespace Seg {
  using T = ull;
  T op(T a, T b) { return mult(a, b); }
  T e() { return 1; }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  cin >> x >> q >> M;
  RED = FastMod(M);

  const int MX = 1e6;
  segtree<Seg::T, Seg::op, Seg::e> seg(MX);

  auto add = [&](int p) {
    seg.set(p, seg.get(p) + 1);
  };

  ull prod = 1;

  map<int, int> divs;
  int orig = x;

  map<int, int> mp;
  for (int i = 2; i*i <= orig; i++) {
    if (x % i == 0) {
      while (x % i == 0) {
        if (i > 2) {
          if (i > MX) {
            mp[i]++;
          }
          else add(i);
        }
        x /= i;
      }
    }
  }
  if (x > 2) {
    if (x > MX) {
      mp[x]++;
    }
    else add(x);
  }
  for (auto [_, c]: mp) {
    prod = mult(prod, c+1);
  }

  REP(q) {
    int xi; cin >> xi;
    while (xi > 1) {
      int p = spf[xi];
      if (p > 2) add(p);
      xi /= p;
    }
    ull ans = mult(prod, seg.all_prod()) % M;
    cout << ans << '\n';
  }

  // int N; cin >> N;
  // for (int x = 1; x <= N; x++) {
  //   int cnt = 0;
  //   for (int i = 1; i <= x; i++) {
  //     bool has = false;
  //     int sum = 0;
  //     for (int j = i; j >= 1; j--) {
  //       sum += j;
  //       if (sum == x) {
  //         has = true;
  //         break;
  //       }
  //     }
  //     if (has) cnt++;
  //   }
  //   cout << x << ": " << cnt << '\n';
  // }
}
