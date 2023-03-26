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

const int maxn = 2e5+5;
int N, Q;

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
  int op(int a, int b) { return a + b; }

  int e() { return 0; }
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
        dfs(j, i, t);
      }
    tout[i] = t-1;
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
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init() {
    int root = is_0_index ? 0 : 1;
    int t = 0;
    dfs(root, -1, t);
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

  int dist(int a, int b) {
    int lc = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[lc];
  }

  bool is_ancestor(int lca, int a) {
    return tin[lca] <= tin[a] && tin[a] <= tout[lca];
  }

  bool on_path(int u, int v, int lca, int x) {
    return is_ancestor(lca, x) && (is_ancestor(x, u) || is_ancestor(x, v));
  }

  // Returns the child of lca whose subtree contains a.
  int get_child_of(int lca, int a) {
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] > depth[lca]) a = aa;
    }
    return a;
  }

  int getpar(int i, int d) {
    assert(d <= 20);
    F0Rd(k, min(maxk, 5)) {
      if (d & (1 << k)) {
        i = par[k][i];
      }
    }
    return i;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N;
  Tree tree(N);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    tree.add_edge(a, b);
  }
  tree.init();

  const int MX = 20;
  using SEG = segtree<int, Seg::op, Seg::e>;
  vector<SEG> segs(MX + 1, SEG(N));

  auto sum_vertex = [&](int v, int d) {
    int l = tree.tin[v];
    int r = tree.tout[v];
    return segs[d].prod(l, r);
  };
  auto add_path = [&](int v, int lca, int d, int x) {
    int i = tree.tin[v];
    segs[d].set(i, segs[d].get(i) + x);
    if (lca != -1) {
      int j = tree.tin[lca];
      segs[d].set(j, segs[d].get(j) - x);
    }
  };
  auto add_vertex = [&](int v, int d, int x) {
    return add_path(v, tree.par[0][v], d, x);
  };

  cin >> Q;
  while (Q--) {
    int t; cin >> t;
    if (t == 1) {
      int v; cin >> v; v--;
      int ans = 0;
      for (int d = 0; d <= MX; d++) {
        if (v == -1) break;
        ans += sum_vertex(v, d);
        v = tree.par[0][v];
      }
      cout << ans << '\n';
    }
    else {
      int u, v, k, d; cin >> u >> v >> k >> d;
      u--, v--;
      int lca = tree.lca(u, v);
      add_path(u, lca, d, k);
      add_path(v, lca, d, k);

      // cout << "adding " << u << ' ' << v << ' ' << d << endl;
      for (int D = d; D >= 0; D--) {
        if (lca == -1) break;
        add_vertex(lca, D, k);
        if (D > 0) add_vertex(lca, D-1, k);
        // special case if at the root
        if (lca == 0) {
          D -= 2;
          while (D >= 0) {
            add_vertex(lca, D, k);
            D--;
          }
          break;
        }
        else {
          lca = tree.par[0][lca];
        }
      }
    }
  }
}
