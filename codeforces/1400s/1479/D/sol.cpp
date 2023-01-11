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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// }}}

const int maxn = 3e5+5;
int N, Q, A[maxn], hsh[maxn];

// persistent segtree {{{
const int MV = 7000000;
int l[MV], r[MV];
int sum[MV];
int nv = 0;
int rp[maxn];

int build(int tl, int tr) {
  if (tl == tr) return nv++;
  int tm = (tl + tr) / 2;
  int cv = nv;
  nv++;
  l[cv] = build(tl, tm);
  r[cv] = build(tm+1, tr);
  sum[cv] = sum[l[cv]] ^ sum[r[cv]];
  return cv;
}

int query(int v, int tl, int tr, int L, int R) {
  if (L > R) return 0;
  if (L == tl && R == tr) return sum[v];
  int tm = (tl+tr)/2;
  return query(l[v], tl, tm, L, min(R, tm)) ^ query(r[v], tm+1, tr, max(L, tm+1), R);
}

int update(int v, int tl, int tr, int pos, int new_val) {
  if (tl == tr) {
    sum[nv] = new_val ^ sum[v];
    return nv++;
  }
  int tm = (tl+tr)/2;
  if (pos <= tm) {
    int cv = nv; nv++;
    l[cv] = update(l[v], tl, tm, pos, new_val);
    r[cv] = r[v];
    sum[cv] = sum[l[cv]] ^ sum[r[cv]];
    return cv;
  } else {
    int cv = nv; nv++;
    l[cv] = l[v];
    r[cv] = update(r[v], tm+1, tr, pos, new_val);
    sum[cv] = sum[l[cv]] ^ sum[r[cv]];
    return cv;
  }
}

int smallest_l(int v1, int v2, int tl, int tr, int lbound, int alc, int target) {
  if (tl == tr) {
    int ans = sum[v1] ^ sum[v2] ^ (tl <= alc ? hsh[alc] : 0);
    return ans == target ? tl : -1;
  }
  int tm = (tl+tr)/2;
  if (lbound > tm) { // if lbound is on right, have to go right
    return smallest_l(r[v1], r[v2], tm+1, tr, lbound, alc, target);
  }
  else {
    int ans = sum[r[v1]] ^ sum[r[v2]] ^ (tm+1 <= alc ? hsh[alc] : 0);
    // if leftmost-right fails, have to go left
    if (ans != target) {
      return smallest_l(l[v1], l[v2], tl, tm, lbound, alc, target ^ sum[r[v1]] ^ sum[r[v2]]);
    }
    else {
      // else if left-most right succeeds, then go right
      return smallest_l(r[v1], r[v2], tm+1, tr, lbound, alc, target);
    }
  }
}
// }}}

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
    rp[i] = update(rp[p], 1, N, A[i], hsh[A[i]]);
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
    dfs(root, 0, t);
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
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> Q;

  for (int i = 1; i <= N; i++) {
    hsh[i] = rng();
    cin >> A[i];
  }

  Tree tree(N, false);
  REP(N-1) {
    int a, b; cin >> a >> b;
    tree.add_edge(a, b);
  }
  rp[0] = build(1, N);
  tree.init();

  auto pathXor = [&](int u, int v, int lc, int l, int r) -> int {
    int ans = query(rp[u], 1, N, l, r) ^ query(rp[v], 1, N, l, r);
    if (l <= A[lc] && A[lc] <= r) ans ^= hsh[A[lc]];
    return ans;
  };

  while (Q--) {
    int u, v, l, r; cin >> u >> v >> l >> r;
    int lc = tree.lca(u, v);
    int X = pathXor(u, v, lc, l, r);
    if (X == 0) {
      cout << -1 << '\n';
    }
    else {
      int target = pathXor(u, v, lc, l, N);
      int ans = smallest_l(rp[u], rp[v], 1, N, l, A[lc], target);
      cout << ans << '\n';
    }
  }
}
