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

struct Seg {
  int pfx, sfx, sum, tot;
  Seg(int a, int b, int c, int d) {
    pfx = max(0, a);
    sfx = max(0, b);
    sum = c;
    tot = max(0, d);
  }
};

Seg merge(Seg a, Seg b) {
  return Seg(max(a.pfx, a.sum + b.pfx), max(b.sfx, b.sum + a.sfx), a.sum + b.sum, max(a.tot, max(b.tot, a.sfx + b.pfx)));
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<vector<int>> pfx;
  vector<vector<Seg>> segs;
  vector<int> tin, tout;
  vector<int> A;

  void dfs(int i, int p, int cur, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    int ncur = cur + A[i];
    pfx[0][i] = ncur;
    segs[0][i] = Seg(A[i], A[i], A[i], A[i]);

    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
      if (par[k-1][i] != -1) {
        segs[k][i] = merge(segs[k-1][i], segs[k-1][par[k-1][i]]);
        pfx[k][i] = max(pfx[k-1][i], pfx[k-1][par[k-1][i]]);
      }
    }
    for (int j: adj[i]) if (j != p) {
        dfs(j, i, ncur, t);
      }
    tout[i] = t-1;
  }

  const int INF = 2e9;
  Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    pfx = vector<vector<int>>(maxk, vector<int>(sz, -INF));
    segs = vector<vector<Seg>>(maxk, vector<Seg>(sz, Seg(0, 0, 0, 0)));
    tin.resize(sz);
    tout.resize(sz);
    A.resize(sz);
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init() {
    int root = is_0_index ? 0 : 1;
    int t = 0;
    dfs(root, -1, 0, t);
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

  int getMaxSubarray(int lca, int a) {
    Seg seg(0, 0, 0, 0);
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] >= depth[lca]) {
        seg = merge(seg, segs[k][a]);
        a = aa;
      }
    }
    // cout << seg.pfx << ' ' << seg.sfx << ' ' << seg.sum << ' ' << seg.tot << endl;
    return seg.tot;
  }

  int getMaxPfx(int lca, int a) {
    int ans = pfx[0][lca];
    for (int k = maxk-1; k >= 0; k--) {
      int aa = par[k][a];
      if (aa != -1 && depth[aa] >= depth[lca]) {
        ckmax(ans, pfx[k][a]);
        a = aa;
      }
    }
    int sub = lca == 1 ? 0 : pfx[0][par[0][lca]];
    return ans - sub;
  }

  int getMaxOnPath(int u, int v) {
    if (u == v) return max(0, A[u]);
    int lc = lca(u, v);
    // DEBUG(lc);
    if (lc == u) {
      // cout << "OK " << endl;
      // cout << getMaxPfx(lc, v) << ' ' << getMaxSubarray(lc, v) << endl;
      return max(getMaxPfx(lc, v), getMaxSubarray(lc, v));
    }
    else if (lc == v) {
      return max(getMaxPfx(lc, u), getMaxSubarray(lc, u));
    }
    else {
      int mx = max(getMaxSubarray(lc, u), getMaxSubarray(lc, v));
      int sum = getMaxPfx(lc, u) + getMaxPfx(lc, v) - A[lc];
      ckmax(mx, sum);
      return mx;
    }
  }
};

void solve() {
  int N; cin >> N;
  Tree treeMx(N+5, false), treeMn(N+5, false);
  treeMx.A[1] = 1;
  treeMn.A[1] = -1;
  int n = 1;

  vector<array<int, 3>> queries;
  F0R(i, N) {
    string s; cin >> s;
    if (s == "+") {
      int v, x; cin >> v >> x;
      n++;
      treeMx.A[n] = x;
      treeMx.add_edge(v, n);
      treeMn.A[n] = -x;
      treeMn.add_edge(v, n);
    }
    else {
      int u, v, k; cin >> u >> v >> k;
      queries.push_back({u, v, k});
    }
  }
  treeMx.init();
  treeMn.init();

  for (auto [u, v, k]: queries) {
    int mx = treeMx.getMaxOnPath(u, v);
    int mn = -treeMn.getMaxOnPath(u, v);
    // cout << "query " << u << ' ' << v << ' ' << k << endl;
    // DEBUG(mn);
    // DEBUG(mx);
    cout << (mn <= k && k <= mx ? "YES" : "NO") << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
