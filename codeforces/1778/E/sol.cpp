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

struct XorBasis {
  static const int d = 30;
  int basis[d];
  int sz = 0;
  XorBasis() {
    memset(basis, 0, sizeof basis);
  }
  void insertVector(int mask) {
    for (int i = 0; i < d; i++) {
      if ((mask & 1 << i) == 0) continue; // continue if i != f(mask)

      if (!basis[i]) { // If there is no basis vector with the i'th bit set, then insert this vector into the basis
        basis[i] = mask;
        ++sz;
        return;
      }

      mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
    }
  }
};

XorBasis merge(XorBasis a, XorBasis b) {
  F0R(i, XorBasis::d) if (b.basis[i]) a.insertVector(b.basis[i]);
  return a;
}

int max_subset(XorBasis& xb) {
  int index = 0;
  F0Rd(i, XorBasis::d) {
    int maxInd = index;
    int maxEle = -999999;
    for (int j = index; j < XorBasis::d; j++) {
      if ((xb.basis[j] & (1 << i)) != 0
          && xb.basis[j] > maxEle) {
        maxEle = xb.basis[j], maxInd = j;
      }
    }

    if (maxEle == -999999) continue;
    swap(xb.basis[index], xb.basis[maxInd]);
    maxInd = index;

    F0R(j, XorBasis::d) {
      if (j != maxInd &&
          (xb.basis[j] & (1 << i)) != 0)
        xb.basis[j] ^= xb.basis[maxInd];
    }
    index++;
  }
  int res = 0;
  for (int i = 0; i < XorBasis::d; i++) res ^= xb.basis[i];
  return res;
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<vector<int>> child;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<map<int, int>> toIdx;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = depth[p] + 1;
    par[0][i] = p;
    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    int idx = 0;
    for (int j: adj[i]) if (j != p) {
        child[i].push_back(j);
        toIdx[i][j] = idx++;
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
    child.resize(sz);
    toIdx.resize(sz);
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

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }
  Tree tree(N);
  F0R(i, N-1) {
    int a, b; cin >> a >> b;
    a--; b--;
    tree.add_edge(a, b);
  }
  tree.init();

  vector<vector<XorBasis>> pfx(N), sfx(N);
  vector<XorBasis> par(N);

  XorBasis all;
  F0R(i, N) all.insertVector(A[i]);
  auto get_basis = [&](int i, int r) -> XorBasis {
    if (i == r) return all;
    if (tree.is_ancestor(i, r)) {
      r = tree.get_child_of(i, r);
      XorBasis ret = par[i];
      int idx = tree.toIdx[i][r];
      if (idx > 0) ret = merge(ret, pfx[i][idx-1]);
      if (idx + 1 < sz(tree.child[i])) {
        ret = merge(ret, sfx[i][idx+1]);
      }
      return ret;
    }
    else {
      return sfx[i][0];
    }
  };

  y_combinator([&](auto dfs, int i) -> void {
    pfx[i].resize(sz(tree.child[i]));
    sfx[i].resize(sz(tree.child[i]));
    XorBasis cur;
    cur.insertVector(A[i]);
    if (sz(tree.child[i]) > 0) {
      F0R(idx, sz(tree.child[i])) {
        int j = tree.child[i][idx];
        dfs(j);
        cur = merge(cur, sfx[j][0]);
        pfx[i][idx] = cur;
      }
      cur = XorBasis();
      cur.insertVector(A[i]);
      F0Rd(idx, sz(tree.child[i])) {
        int j = tree.child[i][idx];
        cur = merge(cur, sfx[j][0]);
        sfx[i][idx] = cur;
      }
    }
    else {
      sfx[i].push_back(cur);
    }
  })(0);
  par[0].insertVector(A[0]);
  y_combinator([&](auto dfs, int i) -> void {
    for (int j: tree.child[i]) {
      par[j] = get_basis(i, j);
      par[j].insertVector(A[j]);
      dfs(j);
    }
  })(0);

  int Q; cin >> Q;
  while (Q--) {
    int r, i; cin >> r >> i;
    r--, i--;
    auto basis = get_basis(i, r);
    int ans = max_subset(basis);
    cout << ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
