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

  auto maxpal = y_combinator([&](auto maxpal, const string& s, int i, int j) -> int {
    if (i == j) return 1;
    if (i > j) return 0;
    else return max(maxpal(s, i+1, j), 0),
                     max(maxpal(s, i, j-1),
                     maxpal(s, i+1, j-1) + (s[i] == s[j] ? 2 : 0));
  });

  int ans = 0;
  F0R(i, N) {
    F0R(j, N) {
      int lc = tree.lca(i, j);
      string s;
      int x = i;
      while (x != lc) {
        s += S[x];
        x = tree.par[0][x];
      }
      string t;
      x = j;
      while (true) {
        t += S[x];
        if (x == lc) break;
        x = tree.par[0][x];
      }
      reverse(all(t));
      string T = s + t;
      ckmax(ans, maxpal(T, 0, sz(T) - 1));
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) {
    cout << solve() << '\n';
  }
}
