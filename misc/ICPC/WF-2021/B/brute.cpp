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

// From Atcoder ACL
namespace atcoder { //{{{
  // @param n `0 <= n`
  // @return minimum non-negative `x` s.t. `n <= 2**x`
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
        if (l == r+1) return e();
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
} // namespace atcoder }}}
using atcoder::segtree;

namespace Seg {
  ll op(ll a, ll b) { return max(a, b); }
  ll e() { return 0LL; }
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree { // {{{
  int n, maxk;
  bool is_0_index;
  vector<vector<pair<int, int>>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<ll> pathToRoot;
  segtree<ll, Seg::op, Seg::e> seg;
  vector<vector<vector<pair<ll, int>>>> maxPath;
  // pathSum[k][i] = list of pairs (max weight, which child) 
  // At most length 2
  
  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;

    seg.set(tin[i], pathToRoot[i]);
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (auto [j, w]: adj[i]) if (j != p) {
      pathToRoot[j] = pathToRoot[i] + w;
      dfs(j, i, t);
    }
    tout[i] = t-1;
  }

  ll computeMaxPath(int i, int p) {
    vector<pair<ll, int>> v;
    for (auto [j, w]: adj[i]) if (j != p) {
      ll c = computeMaxPath(j, i) + w;
      v.push_back({c, j});
    }
    sort(all(v)); reverse(all(v));
    ll ret = v.empty() ? 0 : v[0].first;
    for (int j = 0; j < min(2, sz(v)); j++) {
      auto [w, c] = v[j];
      maxPath[0][i].push_back({w - pathToRoot[i], c});
    }

    return ret;
  }

  void dfs2(int i, int p) {
    for (int k = 1; k < maxk; k++) {
      int j = par[k-1][i];
      if (j == -1) {
        par[k][i] = par[k-1][i];
      }
      else {
        auto x = getMaxPathNotChild(k-1, j, i);
        for (auto [w, c]: maxPath[k-1][i]) {
          maxPath[k][i].push_back({max(w, x), c});
        }
      }
    }

    for (auto [j, _]: adj[i]) if (j != p) {
      dfs2(j, i);
    }
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
    pathToRoot.resize(sz, 0);
    seg = segtree<ll, Seg::op, Seg::e>(sz);
    maxPath = vector<vector<vector<pair<ll, int>>>>(maxk, vector<vector<pair<ll, int>>>(sz));
  }
  void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  void init_with_root(int r) {
    int t = 0;
    dfs(r, -1, t);
    computeMaxPath(r, -1);
    dfs2(r, -1);
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

  ll getMaxPathNotChild(int k, int i, int j) {
    ll ans = -pathToRoot[i];
    for (auto [w, c]: maxPath[k][i]) {
      if (!is_ancestor(c, j)) {
        ckmax(ans, w);
      }
    }
    return ans;
  }

  ll getMaxPath(int lca, int i) {
    int orig = i;
    ll ans = -1e18;
    for (auto [w, j]: maxPath[0][i]) {
      ckmax(ans, w);
    }
    i = par[0][i];
    while (i != -1 && depth[i] >= depth[lca]) {
      for (auto [w, j]: maxPath[0][i]) {
        if (!is_ancestor(j, orig)) {
          ckmax(ans, w);
        }
      }
      i = par[0][i];
    }
    /*
    for (int k = maxk-1; k >= 0; k--) {
      int ii = par[k][i];
      if (ii != -1 && depth[ii] >= depth[lca]-1) {
        // int j = get_child_of(ii, i);
        i = ii;
        ckmax(ans, getMaxPathNotChild(k, i, orig));
      }
    }
    */

    // add back path from parent of lca to root
    ans += 2 * pathToRoot[par[0][lca]];
    return ans;
  }
}; // }}}

// If T is an ancestor of K, impossible
// If K is an ancestor of T, can do anything (pick heaviest leaf-to-root path)
// Else let L be lca(K, T).
// Let L' be the child of L that goes to K
// If we pick a leaf outside the subtree of L', then simply subtract its weight
//

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  ll edgeSum = 0;

  Tree tree(N);

  vector<array<int, 3>> edges;
  for (int i = 1; i <= N-1; i++) {
    int a, b, w; cin >> a >> b >> w;
    a--; b--;
    edges.push_back({a, b, w});
    edgeSum += 2 * w;
  }

  struct Query {
    int R, K, T, id;
  };
  vector<Query> queries(Q);
  vector<ll> ans(Q);

  for (int i = 0; i < Q; i++) {
    int R, K, T; cin >> R >> K >> T;
    R--; K--; T--;
    queries[i] = {R, K, T, i}; 
  }
  sort(all(queries), [](auto a, auto b) {
    return a.R < b.R;
  });

  int root = -1;
  for (auto [R, K, T, id]: queries) {
    if (root != R) {
      root = R;
      tree = Tree(N);
      for (auto [a, b, w]: edges) {
        tree.add_edge(a, b, w);
      }
      tree.init_with_root(root);
    }

    int L = tree.lca(K, T);
    if (T == L) {
      ans[id] = -1;
    }
    else if (K == L) {
      ll sub = tree.seg.all_prod();
      ans[id] = edgeSum - sub;
    }
    else {
      int Lp = tree.get_child_of(L, K);
      ll sub = -1e18;
      ckmax(sub, tree.seg.prod(0, tree.tin[Lp]-1));
      ckmax(sub, tree.seg.prod(tree.tout[Lp]+1, N-1));
      ckmax(sub, tree.getMaxPath(Lp, K));
      ans[id] = edgeSum - sub;
    }
  }

  // output
  for (int i = 0; i < Q; i++) {
    if (ans[i] < 0) {
      cout << "impossible\n";
    }
    else {
      cout << ans[i] << '\n';
    }
  }
}
