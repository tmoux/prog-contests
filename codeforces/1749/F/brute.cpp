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
    dfs(root, root, t);
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
    F0Rd(k, maxk-1) {
      if (d & (1 << k)) {
        i = par[k][i];
      }
    }
    return i;
  }
};

int C1[maxn];
using Query = array<int, 5>;

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

  auto onePath = [&](int x, Query q) -> int {
    auto [u, v, lca, k, d] = q;
    if (tree.on_path(u, v, lca, tree.getpar(x, d))) {
      return k;
    }
    else if (tree.dist(x, lca) <= d) return k;
    else return 0;
  };
  cin >> Q;
  vector<Query> queries; // u, v, lca, k, d
  F0R(i, Q) {
    int t; cin >> t;
    if (t == 1) {
      int v; cin >> v; v--;
      int ans = 0;
      for (auto q: queries) {
        ans += onePath(v, q);
      }
      cout << ans << '\n';
    }
    else {
      int u, v, k, d; cin >> u >> v >> k >> d;
      u--, v--;
      queries.push_back({u, v, tree.lca(u, v), k, d});
    }
  }

}

// Process queries in size B blocks.
// (We could also use HLD or something, but this requires less advanced stuff.)
// To check if a vertex v is within distance d of a path,
// first check if the d'th parent of v is on the path.
// Else check if the distance of v to the lca is at most d.
// Otherwise, it's not within distance d.
//
// We also rebuild the tree every Q/B queries.
// To rebuild, we need:
// - adding on a path (prefix sums)
// - Add on everything within distance d of a vertex.
