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

// persistent segtree {{{
const int MV = 20000000;
int l[MV], r[MV];
int sum[MV];
int nv = 0;
int rp[maxn];
const int SZ = maxn;

int build(int tl, int tr) {
  if (tl == tr) return nv++;
  int tm = (tl + tr) / 2;
  int cv = nv;
  nv++;
  l[cv] = build(tl, tm);
  r[cv] = build(tm+1, tr);
  sum[cv] = sum[l[cv]] + sum[r[cv]];
  return cv;
}

int query(int v, int tl, int tr, int L, int R) {
  if (L > R) return 0;
  if (L == tl && R == tr) return sum[v];
  int tm = (tl+tr)/2;
  return query(l[v], tl, tm, L, min(R, tm)) + query(r[v], tm+1, tr, max(L, tm+1), R);
}

int update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    sum[nv] = new_val + sum[v];
    return nv++;
  }
  int tm = (tl+tr)/2;
  if (pos <= tm) {
    int cv = nv; nv++;
    l[cv] = update(l[v], tl, tm, pos, new_val);
    r[cv] = r[v];
    sum[cv] = sum[l[cv]] + sum[r[cv]];
    return cv;
  } else { 
    int cv = nv; nv++;
    l[cv] = l[v];
    r[cv] = update(r[v], tm+1, tr, pos, new_val);
    sum[cv] = sum[l[cv]] + sum[r[cv]];
    return cv;
  }
} 
// }}}

struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  
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

  vector<int> tin, tout;
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

  bool is_ancestor(int lca, int a) {
    return tin[lca] <= tin[a] && tin[a] <= tout[lca];
  }
};

int N, Q, P;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q >> P;
  Tree tree_a(N, false);
  REP(N-1) {
    int u, v; cin >> u >> v;
    tree_a.add_edge(u, v);
  }
  tree_a.init();

  Tree tree_b(N, false);
  REP(N-1) {
    int u, v; cin >> u >> v;
    tree_b.add_edge(u, v);
  }
  tree_b.init();

  y_combinator([&](auto dfs, int i, int p) -> void {
    int r = i == 1 ? build(0, SZ-1) : rp[p];
    r = update(r, 0, SZ-1, tree_b.tin[i], 1);
    rp[i] = update(r, 0, SZ-1, tree_b.tout[i]+1, -1);
    
    for (int j: tree_a.adj[i]) if (j != p) {
      dfs(j, i);
    }
  })(1, 1);

  int ans = 0;

  auto path_query = [&](int A, int B, int C, int D) -> int {
    int lca_a = tree_a.lca(A, B);
    int lca_b = tree_b.lca(C, D);
    auto on_path = [&](int i) -> bool {
      return tree_b.is_ancestor(lca_b, i) && (tree_b.is_ancestor(i, C) || tree_b.is_ancestor(i, D));
    };
    auto g = [&](int i, int j) -> int {
      return query(rp[i], 0, SZ-1, 0, tree_b.tin[j]);
    };
    auto f = [&](int i) -> int {
      int res = g(i, C) + g(i, D) - 2 * g(i, lca_b);
      if (tree_a.is_ancestor(lca_b, i)) res++;
      return res; 
    };
    
    int ans = f(A) + f(B) - 2 * f(lca_a);
    if (on_path(lca_a)) ans++;
    return ans;
  };

  REP(Q) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    int A = (a + ans * P - 1) % N + 1;
    int B = (b + ans * P - 1) % N + 1;
    int C = (c + ans * P - 1) % N + 1;
    int D = (d + ans * P - 1) % N + 1;

    ans = path_query(A, B, C, D);
    cout << ans << '\n';
  }
}
