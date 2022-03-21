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

struct Node {/*{{{*/
  int s, e, m;
  //covers s,e;
  int sum;
  int lazy;
  Node *l, *r;

  Node(int a, int b) {
    s = a;
    e = b;
    sum = 0;
    lazy = 0;
    if (s != e) {
      m = (s+e)/2;
      l = new Node(s,m);
      r = new Node(m+1,e);
    }
    else {
      l = NULL;
      r = NULL;
    }
  }

  void push() {
    if (s != e) {
      l->lazy += lazy;
      l->sum += (l->e - l->s + 1) * lazy;

      r->lazy += lazy;
      r->sum += (r->e - r->s + 1) * lazy;
    }
    lazy = 0;
  }

  void add(int st, int en, int x) {
    //lazy: already accounted for in your own node, not the childs nodes
    if (st <= s && e <= en) {
      lazy += x;
      sum += (e - s + 1) * x;
      return;
    }
    push();
    if (st <= m) {
      l->add(st,en,x);
    }
    if (en > m) {
      r->add(st,en,x);
    }
    sum = l->sum + r->sum;
  }

  int getsum(int st, int en) {
    push();
    //if completely included
    if (st <= s && e <= en) {
      return sum;
    }
    int ret = 0;
    if (st <= m) {
      ret += l->getsum(st,en);
    }
    if (en > m) {
      ret += r->getsum(st,en);
    }
    return ret;
  }
};/*}}}*/

namespace atcoder {/*{{{*/
  // @param n `0 <= n`
  // @return minimum non-negative `x` s.t. `n <= 2**x`
  int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
  }

  template <class S,
           S (*op)(S, S),
           S (*e)(),
           class F,
           S (*mapping)(F, S),
           F (*composition)(F, F),
           F (*id)()>
             struct lazy_segtree {
               public:
                 lazy_segtree() : lazy_segtree(0) {}
                 explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
                 explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
                   log = ceil_pow2(_n);
                   size = 1 << log;
                   d = std::vector<S>(2 * size, e());
                   lz = std::vector<F>(size, id());
                   for (int i = 0; i < _n; i++) d[size + i] = v[i];
                   for (int i = size - 1; i >= 1; i--) {
                     update(i);
                   }
                 }

                 void set(int p, S x) {
                   assert(0 <= p && p < _n);
                   p += size;
                   for (int i = log; i >= 1; i--) push(p >> i);
                   d[p] = x;
                   for (int i = 1; i <= log; i++) update(p >> i);
                 }

                 S get(int p) {
                   assert(0 <= p && p < _n);
                   p += size;
                   for (int i = log; i >= 1; i--) push(p >> i);
                   return d[p];
                 }

                 S prod(int l, int r) {
                   r++; // range [l, r]
                   assert(0 <= l && l <= r && r <= _n);
                   if (l == r) return e();

                   l += size;
                   r += size;

                   for (int i = log; i >= 1; i--) {
                     if (((l >> i) << i) != l) push(l >> i);
                     if (((r >> i) << i) != r) push((r - 1) >> i);
                   }

                   S sml = e(), smr = e();
                   while (l < r) {
                     if (l & 1) sml = op(sml, d[l++]);
                     if (r & 1) smr = op(d[--r], smr);
                     l >>= 1;
                     r >>= 1;
                   }

                   return op(sml, smr);
                 }

                 S all_prod() { return d[1]; }

                 void apply(int p, F f) {
                   assert(0 <= p && p < _n);
                   p += size;
                   for (int i = log; i >= 1; i--) push(p >> i);
                   d[p] = mapping(f, d[p]);
                   for (int i = 1; i <= log; i++) update(p >> i);
                 }
                 void apply(int l, int r, F f) {
                   r++; // range [l, r]
                   assert(0 <= l && l <= r && r <= _n);
                   if (l == r) return;

                   l += size;
                   r += size;

                   for (int i = log; i >= 1; i--) {
                     if (((l >> i) << i) != l) push(l >> i);
                     if (((r >> i) << i) != r) push((r - 1) >> i);
                   }

                   {
                     int l2 = l, r2 = r;
                     while (l < r) {
                       if (l & 1) all_apply(l++, f);
                       if (r & 1) all_apply(--r, f);
                       l >>= 1;
                       r >>= 1;
                     }
                     l = l2;
                     r = r2;
                   }

                   for (int i = 1; i <= log; i++) {
                     if (((l >> i) << i) != l) update(l >> i);
                     if (((r >> i) << i) != r) update((r - 1) >> i);
                   }
                 }

                 template <bool (*g)(S)> int max_right(int l) {
                   return max_right(l, [](S x) { return g(x); });
                 }
                 template <class G> int max_right(int l, G g) {
                   assert(0 <= l && l <= _n);
                   assert(g(e()));
                   if (l == _n) return _n;
                   l += size;
                   for (int i = log; i >= 1; i--) push(l >> i);
                   S sm = e();
                   do {
                     while (l % 2 == 0) l >>= 1;
                     if (!g(op(sm, d[l]))) {
                       while (l < size) {
                         push(l);
                         l = (2 * l);
                         if (g(op(sm, d[l]))) {
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

                 template <bool (*g)(S)> int min_left(int r) {
                   return min_left(r, [](S x) { return g(x); });
                 }
                 template <class G> int min_left(int r, G g) {
                   assert(0 <= r && r <= _n);
                   assert(g(e()));
                   if (r == 0) return 0;
                   r += size;
                   for (int i = log; i >= 1; i--) push((r - 1) >> i);
                   S sm = e();
                   do {
                     r--;
                     while (r > 1 && (r % 2)) r >>= 1;
                     if (!g(op(d[r], sm))) {
                       while (r < size) {
                         push(r);
                         r = (2 * r + 1);
                         if (g(op(d[r], sm))) {
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
                 std::vector<F> lz;

                 void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
                 void all_apply(int k, F f) {
                   d[k] = mapping(f, d[k]);
                   if (k < size) lz[k] = composition(f, lz[k]);
                 }
                 void push(int k) {
                   all_apply(2 * k, lz[k]);
                   all_apply(2 * k + 1, lz[k]);
                   lz[k] = id();
                 }
             };
}  // namespace atcoder}}}
using atcoder::lazy_segtree;

namespace Seg {
  int op(int l, int r) { return l + r; }
  int e() { return 0; }
  int mapping(int add, int r) { return add + r; }
  int composition(int x, int y) { return x + y; };
  int id() { return 0; }
}

using lazy_seg = lazy_segtree<int, Seg::op, Seg::e, int, Seg::mapping, Seg::composition, Seg::id>;
lazy_seg psum[65];

const int maxn = 305;
int spf[maxn];
bool isprime[maxn];
int primeToId[maxn]; int counter = 0;

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    isprime[i] = true;
    primeToId[i] = counter++;
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

vector<pair<int,int>> factors[maxn];

namespace ModInt { //{{{
  template<int MOD>
    struct mod_int {
      int val;

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

      bool operator==(const mod_int& b) const {
        return val == b.val;
      }

      bool operator!=(const mod_int& b) const {
        return !(*this == b);
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

      mod_int& operator++(int) {
        return *this += 1;
      }

      mod_int& operator--(int) {
        return *this -= 1;
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
        i >> x.val; x.val %= MOD;
        return i;
      }
    };
} //}}}
const int MOD = 1e9+7;
using mint = ModInt::mod_int<MOD>;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  for (int x = 1; x <= 300; x++) {
    int y = x;
    map<int,int> cnt;
    while (y > 1) {
      int fac = spf[y];
      cnt[fac]++;
      y /= fac;
    }
    for (auto p: cnt) factors[x].push_back(p);
  }
  int n, q; cin >> n >> q;
  F0R(i, counter) {
    psum[i] = lazy_seg(n);
  }


  F0R(i, n) {
    int x; cin >> x;
    for (auto [p, c]: factors[x]) {
      psum[primeToId[p]].apply(i, c);
    }
  }

  REP(q) {
    string s;
    int l, r;
    cin >> s >> l >> r;
    l--; r--;
    if (s == "MULTIPLY") {
      int x; cin >> x;
      for (auto [p, c]: factors[x]) {
        psum[primeToId[p]].apply(l, r, c);
      }
    }
    else {
      mint ans = 1;
      F0R(p, 301) if (isprime[p]) {
        int k = psum[primeToId[p]].prod(l, r);
        if (k > 0) {
          ans *= mint(p) ^ (k-1);
          ans *= mint(p) - 1;
        }
      }
      cout << ans << '\n';
    }
  }
}
