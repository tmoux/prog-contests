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

int N, Q;

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<vector<int>> atDepth;
  int maxDepth;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    atDepth[depth[i]-1].push_back(i);
    ckmax(maxDepth, depth[i]-1);
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
    atDepth.resize(sz+1);
    maxDepth = 0;
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

  // Returns the child of lca whose subtree contains a.
  int get_child_of(int lca, int a) {
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] > depth[lca]) a = aa;
    }
    return a;
  }
};

Tree tree(1);
const int maxn = 5e5+5;
vector<array<int, 3>> queries[maxn];
int ans[maxn];

int D[2003][2003];

void process(int d) {
  vector<int> dist(N, 2e9);
  vector<pair<int, int>> range(N, {2e9, -2e9});
  queue<int> q;
  for (auto i: tree.atDepth[d]) {
    q.push(i);
    dist[i] = 0;
    range[i] = {i, i};
  }
  while (!q.empty()) {
    int i = q.front(); q.pop();
    for (int j: tree.adj[i]) {
      if (dist[j] > dist[i] + 1) {
        dist[j] = dist[i] + 1;
        q.push(j);
        if (tree.depth[j]-1 > d) {
          ckmin(range[j].first, range[i].first);
          ckmax(range[j].second, range[i].second);
        }
      }
    }
  }

  y_combinator([&](auto dfs, int i, int p) -> void {
    for (int j: tree.adj[i]) {
      if (j != p) {
        dfs(j, i);
        ckmin(range[i].first, range[j].first);
        ckmax(range[i].second, range[j].second);
      }
    }
  })(0, 0);
  y_combinator([&](auto dfs, int i, int p) -> void {
    if (range[i].first > range[i].second) {
      assert(i != 0);
      range[i] = range[p];
    }
    for (int j: tree.adj[i]) {
      if (j != p) {
        dfs(j, i);
      }
    }
  })(0, 0);

  F0R(i, N) {
    // cout << i+1 << ": " << range[i].first+1 << ' ' << range[i].second+1 << endl;
  }

  auto [L, R] = range[0];
  for (int d = 1; d <= R-L; d++) {
    for (int l = L; l+d <= R; l++) {
      int r = l + d;
      D[l][r] = r - l;
      ckmin(D[l][r], tree.dist(l, r));
      if (l+1 <= r) {
        ckmin(D[l][r], 1 + D[l+1][r]);
        ckmin(D[l][r], 1 + D[l][r-1]);
      }
    }
  }

  for (auto [a, b, id]: queries[d]) {
    ans[id] = tree.dist(a, b);
    int tr = dist[a] + dist[b];
    auto p1 = range[a], p2 = range[b];
    if (p1.first > p2.first) swap(p1, p2);
    if (p2.first > p1.second) {
      tr += D[p1.second][p2.first];
    }
    ckmin(ans[id], tr);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;
  tree = Tree(N);
  REP(N-1) {
    int a, b; cin >> a >> b;
    --a, --b;
    tree.add_edge(a, b);
  }
  tree.init();

  F0R(i, Q) {
    int a, b, d; cin >> a >> b >> d;
    if (d > tree.maxDepth) d = 0;
    --a, --b;
    queries[d].push_back({a, b, i});
  }

  for (int d = 0; d < N; d++) {
    if (!queries[d].empty())
      process(d);
  }
  F0R(i, Q) {
    cout << ans[i] << '\n';
  }
}
