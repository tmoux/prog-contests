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
  using S = ll;
  using F = ll;
  S op(S a, S b) { return max(a, b); }
  S e() { return 0; }

  S mapping(F l, S r) {
    return l + r;
  }

  F composition(F a, F b) {
    return a + b;
  }
  F id() { return 0; };
}
using segtree = lazy_segtree<Seg::S, Seg::op, Seg::e, Seg::F, Seg::mapping, Seg::composition, Seg::id>;

using T = pair<int, vector<int>>;
// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout, jmp;
  segtree seg;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = p == -1 ? 0 : depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
        dfs(j, i, t);
      }
    tout[i] = t-1;
    jmp[tin[i]] = tout[i];
  }

  Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    tin.resize(sz);
    tout.resize(sz);
    jmp.resize(sz);
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init(int root) {
    int t = 0;
    dfs(root, -1, t);
    seg = segtree(n);
    F0R(i, n) seg.set(tin[i], depth[i]);
  }

  int lca(int a, int b) {
    if (depth[a] > depth[b]) swap(a, b);
    for (int k = maxk-1; k >= 0; k--) {
      int bb = par[k][b];
      if (bb != -1 && depth[bb] >= depth[a]) b = bb;
    }
    if (a == b) return a;
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      int bb = par[k][b];
      if (aa != bb) {
        a = aa;
        b = bb;
      }
    }
    return par[0][a];
  }

  bool is_ancestor(int lca, int a) {
    return tin[lca] <= tin[a] && tin[a] <= tout[lca];
  }

  // Returns the child of lca whose subtree contains a.
  int get_child_of(int lca, int a) {
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] > depth[lca]) a = aa;
    }
    return a;
  }

  void solve(int i, int p, const vector<vector<T>>& queries, vector<ll>& ans) {
    const int INF = 1e9;
    for (const auto& [id, v]: queries[i]) {
      for (auto j: v) {
        if (is_ancestor(j, i)) {
          int k = get_child_of(j, i);
          seg.apply(0, n-1, -INF);
          seg.apply(tin[k], tout[k], INF);
        }
        else {
          seg.apply(tin[j], tout[j], -INF);
        }
      }

      ckmax(ans[id], seg.all_prod());

      for (auto j: v) {
        if (is_ancestor(j, i)) {
          int k = get_child_of(j, i);
          seg.apply(0, n-1, INF);
          seg.apply(tin[k], tout[k], -INF);
        }
        else {
          seg.apply(tin[j], tout[j], INF);
        }
      }
    }

    for (int j: adj[i]) {
      if (j == p) continue;

      seg.apply(0, n-1, 1);
      seg.apply(tin[j], tout[j], -2);

      solve(j, i, queries, ans);

      seg.apply(tin[j], tout[j], 2);
      seg.apply(0, n-1, -1);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  Tree tree(N);
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    tree.add_edge(a, b);
  }
  tree.init(0);
  vector<vector<T>> queries(N);
  F0R(i, Q) {
    int x, k; cin >> x >> k;
    x--;
    vector<int> v;
    REP(k) {
      int y; cin >> y; y--;
      v.push_back(y);
    }
    queries[x].push_back({i, v});
  }

  vector<ll> ans(Q);
  tree.solve(0, 0, queries, ans);

  for (auto x: ans) {
    cout << x << '\n';
  }
}
