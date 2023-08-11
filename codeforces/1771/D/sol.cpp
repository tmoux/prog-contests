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

// N <= 2000
// Data structure for handling LCA queries and preorder traversals.
struct Tree { // {{{
  int n, maxk;
  string S;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  // vector<vector<int>> up;
  // vector<vector<int>> charST;
  
  void dfs(int i, int p, int& t) {
    // F0R(c, 26) {
    //   up[i][c] = charST[c].empty() ? -1 : charST[c].back();
    // }
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    // charST[S[i]-'a'].push_back(i);
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
      dfs(j, i, t);
    }
    // charST[S[i]-'a'].pop_back();
    tout[i] = t-1;
  }

  Tree(int _n, string _S, bool _is_0_index = true) : n(_n), S(_S), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    tin.resize(sz);
    tout.resize(sz);
    // up.resize(sz, vector<int>(26));
    // charST.resize(26);
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
}; // }}}

int solve() {
  int N; cin >> N;
  string S; cin >> S;
  Tree tree(N, S);
  REP(N-1) {
    int u, v; cin >> u >> v;
    u--; v--;
    tree.add_edge(u, v);
  }
  tree.init();

  // cout << 0 << ' ' << 4 << ": " << tree.get_child_of(0, 4) << endl;

  vector<vector<int>> pal(N, vector<int>(N, -1));
  vector<vector<int>> dp(N, vector<int>(N, -1));

  auto fpal = y_combinator([&](auto fpal, int a, int b) -> int {
    int& res = pal[a][b];
    if (res != -1) return res;
    assert(tree.is_ancestor(a, b) || tree.is_ancestor(b, a));
    if (a == b) return res = 1;
    if (tree.depth[a] >= tree.depth[b]) {
      swap(a, b);
    }
    if (tree.depth[a] + 1 == tree.depth[b]) {
      return res = S[a] == S[b] ? 2 : 1;
    }

    int na = tree.get_child_of(a, b);
    int nb = tree.par[0][b];
    res = 0;
    ckmax(res, fpal(na, b));
    ckmax(res, fpal(a, nb));
    ckmax(res, (S[a] == S[b] ? 2 : 0) + fpal(na, nb));
    return res;
  });

  auto fdp = y_combinator([&](auto fdp, int a, int b) -> int {
    if (dp[a][b] != -1) return dp[a][b];
    int& res = dp[a][b];
    int lc = tree.lca(a, b);
    if (lc == a || lc == b) {
      return fpal(a, b); 
    }
    int pa = tree.par[0][a];
    int pb = tree.par[0][b];
    res = 0;
    ckmax(res, fdp(pa, b));
    ckmax(res, fdp(a, pb));
    ckmax(res, (S[a] == S[b] ? 2 : 0) + fdp(pa, pb));
    return res;
  });

  int ans = 0;
  F0R(i, N) {
    F0R(j, N) {
      ckmax(ans, fdp(i, j));
    }
  }

  // cout << fdp(1, 3) << endl;
  // cout << fpal(0, 2) << endl;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
