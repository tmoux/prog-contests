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

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  // @param n 0
  // @return minimum non-negative Symbol’s value as variable is void: x s.t. Symbol’s value as variable is void: n
  int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
  }

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
      r++; // make range [l, r] inclusive.
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
      r++;
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

namespace Seg {
  struct S {
    int pfx0, sfx0, mx0;
    int pfx1, sfx1, mx1;
    int len;
  };
  using F = int;
  S op(S a, S b) {
    int pfx0 = a.pfx0 == a.len ? a.len + b.pfx0 : a.pfx0;
    int sfx0 = b.sfx0 == b.len ? a.sfx0 + b.len : b.sfx0;
    int mx0 = max({a.mx0, b.mx0, pfx0, sfx0, a.sfx0 + b.pfx0});

    int pfx1 = a.pfx1 == a.len ? a.len + b.pfx1 : a.pfx1;
    int sfx1 = b.sfx1 == b.len ? a.sfx1 + b.len : b.sfx1;
    int mx1 = max({a.mx1, b.mx1, pfx1, sfx1, a.sfx1 + b.pfx1});

    return {pfx0, sfx0, mx0, pfx1, sfx1, mx1, a.len + b.len};
  };
  S e() { return {0, 0, 0, 0, 0, 0, 0}; }

  S mapping(F l, S r) {
    if (l) {
      swap(r.pfx0, r.pfx1);
      swap(r.sfx0, r.sfx1);
      swap(r.mx0, r.mx1);
    }
    return r;
  }
  F composition(F a, F b) {
    return a ^ b;
  }
  F id() { return 0; };

  S init(bool b) {
    if (!b) {
      return {1, 1, 1, 0, 0, 0, 1};
    }
    else {
      return {0, 0, 0, 1, 1, 1, 1};
    }
  }
}
using segtree = lazy_segtree<Seg::S, Seg::op, Seg::e, Seg::F, Seg::mapping, Seg::composition, Seg::id>;


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  int Q; cin >> Q;
  string s; cin >> s;

  segtree seg(N);
  F0R(i, N) seg.set(i, Seg::init(s[i] - '0'));

  REP(Q) {
    int t; cin >> t;
    int L, R; cin >> L >> R;
    L--, R--;
    if (t == 1) {
      seg.apply(L, R, 1);
    }
    else {
      auto ans = seg.prod(L, R);
      cout << ans.mx1 << '\n';
    }
  }
}
