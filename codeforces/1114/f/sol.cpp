#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

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
  mint op(mint l, mint r) { return l * r; }
  mint e() { return mint(1); }
  mint mapping(mint mult, mint r) { return mult * r; }
  mint composition(mint x, mint y) { return x * y; };
  mint id() { return mint(1); }
}

using lazy_seg = lazy_segtree<mint, Seg::op, Seg::e, mint, Seg::mapping, Seg::composition, Seg::id>;

namespace Seg2 {
  ll op(ll l, ll r) { return l | r; }
  ll e() { return 0LL; }
  ll mapping(ll mult, ll r) { return mult | r; }
  ll composition(ll x, ll y) { return x | y; };
  ll id() { return 0LL; }
}
using bit_seg = lazy_segtree<ll, Seg2::op, Seg2::e, ll, Seg2::mapping, Seg2::composition, Seg2::id>;

struct Node {
	int s, e, m;
	//covers s,e;
	mint sum;
	mint lazy;
	Node *l, *r;
	
	Node(int a, int b) {
		s = a;
		e = b;
		sum = 1;
		lazy = 1;
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
			l->lazy *= lazy;
			l->sum *= lazy ^ (l->e - l->s + 1);

			r->lazy *= lazy;
			r->sum *= lazy ^ (r->e - r->s + 1);
		}
		lazy = 1;
	}

	void add(int st, int en, mint x) {
		//lazy: already accounted for in your own node, not the childs nodes
		if (st <= s && e <= en) {
			lazy *= x;
      sum *= x ^ (e - s + 1);
			return;
		}
		push();
		if (st <= m) {
			l->add(st,en,x);
		}
		if (en > m) {
			r->add(st,en,x);
		}
		sum = l->sum * r->sum;
	}

	mint getsum(int st, int en) {
		push();
		//if completely included
		if (st <= s && e <= en) {
			return sum;
		}
		mint ret = 1;
		if (st <= m) {
			ret *= l->getsum(st,en);
		}
		if (en > m) {
			ret *= r->getsum(st,en);
		}
		return ret;
	}
};

const int maxn = 305;
int spf[maxn];
int prime[65];
int primeToId[maxn]; int counter = 0;

void init_spf() {
  spf[1] = 1;
  for (int i = 2; i < maxn; i++) if (!spf[i]) {
    prime[counter] = i;
    primeToId[i] = counter++;
    for (int j = i; j < maxn; j += i) {
      if (!spf[j]) spf[j] = i;
    }
  }
}

ll mask[maxn];

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  init_spf();
  for (int x = 1; x <= 300; x++) {
    int y = x;
    while (y > 1) {
      int fac = spf[y];
      mask[x] |= 1LL << primeToId[fac];
      y /= fac;
    }
  }
  int n, q; cin >> n >> q;
  vector<mint> a(n);
  vector<ll> b(n);
  F0R(i, n) {
    int x; cin >> x;
    a[i] = mint(x);
    b[i] = mask[x];
  }
  // lazy_seg productSeg(a);
  Node productSeg = Node(0, n-1);
  F0R(i, n) productSeg.add(i, i, a[i]);
  bit_seg bitSeg(b);

  REP(q) {
    string s;
    int l, r;
    cin >> s >> l >> r;
    l--; r--;
    if (s == "MULTIPLY") {
      int x; cin >> x;
      productSeg.add(l, r, x);
      bitSeg.apply(l, r, mask[x]);

      /*
      FOR(i, l, r+1) {
        a[i] *= x;
        b[i] |= mask[x];
      }
      */
    }
    else {
      mint ans = productSeg.getsum(l, r);
      ll pmask = bitSeg.prod(l, r);

      /*
      mint p = mint(1);
      ll q = 0LL;
      FOR(i, l, r+1) {
        p *= a[i];
        q |= b[i];
      }
      */
      // cout << ans << ' ' << p << '\n';
      // cout << pmask << ' ' << q << '\n';
      // assert(ans == p);
      // assert(pmask == q);

      //F0R(i, counter) {
      //  if (pmask & (1LL<<i)) {
      //    cout << "bit " << prime[i] << endl;
      //  }
      //}

      F0R(i, counter) {
        if (pmask & (1LL<<i)) {
          ans *= (mint(1) - mint(prime[i]).inverse());
        }
      }
      cout << ans << '\n';
    }
  }
}
