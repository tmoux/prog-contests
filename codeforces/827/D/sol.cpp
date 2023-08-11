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
int N, M, ans[maxn];

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<array<int, 3>>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<vector<int>> mx;
  vector<set<pair<int, int>>> paths;

  void dfs(int i, int p, int w) {
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    mx[0][i] = w;
    for (int k = 1; k < maxk; k++) {
      mx[k][i] = max(mx[k-1][i], par[k-1][i] == -1 ? 0 : mx[k-1][par[k-1][i]]);
    }
    for (auto [j, w, id]: adj[i]) if (j != p) {
      dfs(j, i, w);
    }
  }

  void merge(set<pair<int, int>>& a, set<pair<int, int>>& b) {
    if (sz(a) < sz(b)) swap(a, b);
    for (auto p: b) {
      if (a.count(p)) a.erase(p);
      else a.insert(p);
    }
  }

  void dfs2(int i, int p) {
    for (auto [j, w, id]: adj[i]) {
      if (j == p) continue;
      dfs2(j, i);
      if (paths[j].empty()) {
        // bridge
        ans[id] = -1;
      }
      else {
        ans[id] = paths[j].begin()->first - 1;
        merge(paths[i], paths[j]);
      }
    }
  }

  Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    mx = vector<vector<int>>(maxk, vector<int>(sz, 0));
    paths.resize(sz);
  }
  void add_edge(int u, int v, int w, int id) {
    adj[u].push_back({v, w, id});
    adj[v].push_back({u, w, id});
  }

  void init() {
    int root = is_0_index ? 0 : 1;
    dfs(root, root, 0);
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

  int max_path_lca(int lca, int a) {
    int res = 0;
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] >= depth[lca]) {
        ckmax(res, mx[k][a]);
        a = aa;
      }
    }
    return res;
  }

  int max_path(int a, int b) {
    int lc = lca(a, b);
    return max(max_path_lca(lc, a), max_path_lca(lc, b));
  }
};

struct DSU {
  int n;
  vector<int> par;
  DSU(int _n) {
    n = _n;
    par.resize(n+1, -1);
  }

  int Find(int i) {
    return par[i] < 0 ? i : par[i] = Find(par[i]);
  }

  bool Union(int x, int y) { //return true if x and y were not connected
    x = Find(x);
    y = Find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;

  vector<array<int, 4>> edges;
  F0R(i, M) {
    int a, b, w; cin >> a >> b >> w;
    a--, b--;
    edges.push_back({w, a, b, i});
  }
  sort(all(edges));
  DSU dsu(N);

  vector<array<int, 4>> notInMst;
  Tree tree(N);
  for (auto [w, a, b, id]: edges) {
    if (dsu.Find(a) != dsu.Find(b)) {
      dsu.Union(a, b);
      tree.add_edge(a, b, w, id);
    }
    else {
      notInMst.push_back({w, a, b, id});
      tree.paths[a].insert({w, id});
      tree.paths[b].insert({w, id});
    }
  }
  tree.init();

  for (auto [w, a, b, id]: notInMst) {
    ans[id] = tree.max_path(a, b) - 1;
  }

  tree.dfs2(0, 0);

  F0R(i, M) {
    cout << ans[i] << " \n"[i == M-1];
  }
}
