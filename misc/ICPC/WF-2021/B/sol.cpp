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

struct Top2 {
  pair<ll, int> a[2] = {
    {-1e18, -1},
    {-1e18, -1}
  };

  void insert(pair<ll, int> x) {
    if (x.first > a[0].first) {
      a[1] = a[0];
      a[0] = x;
    }
    else if (x.first > a[1].first) {
      a[1] = x;
    }
  }
};

// Data structure for handling LCA queries and preorder traversals.
struct Tree { // {{{
  int n, maxk;
  bool is_0_index;
  vector<vector<pair<int, int>>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<ll> pathToRoot;
  vector<ll> pfx, sfx;
  vector<vector<Top2>> maxPath;
  // pathSum[k][i] = list of pairs (max weight, which child) 
  // At most length 2
  
  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;

    pfx[tin[i]] = sfx[tin[i]] = pathToRoot[i];
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
      maxPath[0][i].insert({w - pathToRoot[i], c});
    }

    return ret;
  }

  void dfs2(int i, int p) {
    for (int k = 1; k < maxk; k++) {
      int j = par[k-1][i];
      if (j == -1) {
        maxPath[k][i] = maxPath[k-1][i];
      }
      else {
        maxPath[k][i] = maxPath[k-1][i];
        auto p = getMaxPathNotChild(k-1, j, i);
        maxPath[k][i].insert(p);
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
    pfx.resize(sz);
    sfx.resize(sz);
    maxPath = vector<vector<Top2>>(maxk, vector<Top2>(sz));
  }
  void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  void init_with_root(int r) {
    int t = 0;
    dfs(r, -1, t);
    for (int i = 1; i < n; i++) ckmax(pfx[i], pfx[i-1]);
    for (int i = n-2; i >= 0; i--) ckmax(sfx[i], sfx[i+1]);
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

  pair<ll, int> getMaxPathNotChild(int k, int i, int j) {
    for (int z = 0; z < 2; z++) {
      auto [w, c] = maxPath[k][i].a[z];
      if (c != -1 && !is_ancestor(c, j)) {
        return {w, c};
      }
    }
    return {-pathToRoot[i], i};
  }

  ll getMaxPath(int lca, int i) {
    int orig = i;
    ll ans = -1e18;
    for (int z = 0; z < 2; z++) {
      auto [w, c] = maxPath[0][i].a[z];
      if (c != -1) ckmax(ans, w);
    }
    i = par[0][i];
    for (int k = maxk-1; k >= 0; k--) {
      int ii = par[k][i];
      if (ii != -1 && depth[ii] >= depth[lca]-1) {
        ckmax(ans, getMaxPathNotChild(k, i, orig).first);
        i = ii;
      }
    }

    // add back path from parent of lca to root
    ans += 2 * pathToRoot[par[0][lca]];
    return ans;
  }
}; // }}}

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
      ll sub = tree.sfx[0];
      ans[id] = edgeSum - sub;
    }
    else {
      int Lp = tree.get_child_of(L, K);
      ll sub = 0;
      if (tree.tin[Lp] > 0) ckmax(sub, tree.pfx[tree.tin[Lp]-1]);
      if (tree.tout[Lp]+1 < N) ckmax(sub, tree.sfx[tree.tout[Lp]+1]);
      ckmax(sub, tree.getMaxPath(Lp, K));
      ans[id] = edgeSum - sub;
    }
  }

  for (int i = 0; i < Q; i++) {
    if (ans[i] < 0) cout << "impossible\n";
    else cout << ans[i] << '\n';
  }
}
