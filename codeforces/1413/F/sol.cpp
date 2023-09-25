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
  using S = array<int, 2>;
  using F = int;
  S op(S a, S b) { return {max(a[0], b[0]), max(a[1], b[1])};}
  S e() { return {0, 0}; }

  S mapping(F l, S r) {
    if (l) return {r[1], r[0]};
    else return r;
  }
  F composition(F a, F b) {
    return a ^ b;
  }
  F id() { return 0; };

  S init(int d, int p) {
    if (p == 0) return {d, 0};
    else return {0, d};
  }
}
using segtree = lazy_segtree<Seg::S, Seg::op, Seg::e, Seg::F, Seg::mapping, Seg::composition, Seg::id>;

const int maxn = 5e5+5;
int N, Q;
vector<array<int, 3>> adj[maxn];
int ans[maxn];

pair<int, int> mx = {-1, -1};

void find_diam(int i, int p, int d) {
  ckmax(mx, {d, i});
  for (auto [j, w, id]: adj[i]) {
    if (j == p) continue;
    find_diam(j, i, d+1);
  }
}

int idToNode[maxn];
int tin[maxn], tout[maxn], t;
int depth[maxn], P[maxn];
void dfs(int i, int p, int d) {
  tin[i] = t++;
  depth[i] = d;
  for (auto [j, w, id]: adj[i]) {
    if (j == p) continue;
    P[j] = P[i] ^ w;
    idToNode[id] = j;
    dfs(j, i, d+1);
  }
  tout[i] = t-1;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  F0R(i, N-1) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].push_back({v, w, i});
    adj[v].push_back({u, w, i});
  }
  find_diam(1, 1, 0);
  int r1 = mx.second;
  mx = {-1, -1};
  find_diam(r1, r1, 0);
  int r2 = mx.second;

  cin >> Q;
  vector<int> queries(Q);
  F0R(i, Q) {
    int id; cin >> id; id--;
    queries[i] = id;
  }

  for (int root : {r1, r2}) {
    t = 0;
    P[root] = 0;
    dfs(root, root, 0);
    segtree seg(N);
    FOR(i, 1, N+1) {
      seg.set(tin[i], Seg::init(depth[i], P[i]));
    }
    F0R(i, Q) {
      int x = idToNode[queries[i]];
      seg.apply(tin[x], tout[x], 1);
      ckmax(ans[i], seg.all_prod()[0]);
    }

  }

  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}
