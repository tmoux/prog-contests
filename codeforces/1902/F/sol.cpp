// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template
#define REP(n) for (int _=0; _<(n); _++)
#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
 
#define sz(x) (int)(x).size()
#define all(x) x.begin(), x.end()
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

namespace std {
  template<class Fun>
  class y_combinator_result {
    Fun fun_;
  public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
   
    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
      return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
  };
   
  template<class Fun>
  decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
  }
} // namespace std

#define DEBUG(x) cerr << #x << ": " << x << '\n'
template<typename A, typename B> 
ostream& operator<<(ostream &os, const pair<A, B> &p) { 
  return os << '(' << p.first << ", " << p.second << ')'; 
}
template<typename T_container, 
  typename T = typename enable_if<!is_same<T_container, string>::value, 
  typename T_container::value_type>::type> 
ostream& operator<<(ostream &os, const T_container &v) { 
  os << '['; string sep; 
  for (const T &x : v) 
    os << sep << x, sep = ", "; 
  return os << ']'; 
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T = uint32_t, int LOG_A = 20>
struct XorBasis {
  array<T, LOG_A> basis;
  int basis_size = 0;
  XorBasis() {
    fill(all(basis), 0);
  }

  T getBit(T x, int i) {
    return x & (1LL << i);
  }

  // return true if not in span
  bool insertVector(T mask) {
    if (basis_size == LOG_A) return false;
    if (!mask) return false;
    for (int i = LOG_A - 1; i >= 0; i--) {
      if (!(mask & (1 << i))) continue;
      if (!basis[i]) {
        basis[i] = mask;
        basis_size++;
        return true;
      }
      mask ^= basis[i];
    }
    return false;
  }
};

const int LOG = 20;
using XB = XorBasis<int, LOG>;

XB merge(XB a, const XB& b) {
  for (int k = LOG-1; k >= 0; k--) {
    a.insertVector(b.basis[k]);
  }
  return a;
}

// Data structure for handling LCA queries and preorder traversals.
struct Tree {
  int n, maxk;
  vector<int> A;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<vector<int>> par;
  vector<int> tin, tout;
  vector<vector<pair<int, int>>> basis;

  void dfs(int i, int p, int& t) {
    tin[i] = t++;
    depth[i] = p == -1 ? 0 : depth[p] + 1;
    par[0][i] = p;
    if (p == -1) basis[i] = {{A[i], i}};
    else {
      XB cur;
      basis[i] = {{A[i], i}};
      cur.insertVector(A[i]);
      for (auto [x, j]: basis[p]) {
        if (cur.insertVector(x)) {
          basis[i].emplace_back(x, j);
        }
      }
    }

    for (int k = 1; k < maxk; k++) {
      par[k][i] = par[k-1][i] == -1 ? -1 : par[k-1][par[k-1][i]];
    }
    for (int j: adj[i]) if (j != p) {
        dfs(j, i, t);
      }
    tout[i] = t-1;
  }

  Tree(int _n, vector<int> _A, bool _is_0_index = true) : n(_n), A(_A), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    par = vector<vector<int>>(maxk, vector<int>(sz, -1));
    basis.resize(sz);
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

  XB getBasisLca(int i, int lc) {
    XB ret;
    for (auto [x, j]: basis[i]) {
      if (depth[j] >= depth[lc]) ret.insertVector(x);
      else break;
    }
    return ret;
  }

  XB getBasis(int x, int y) {
    int lc = lca(x, y);
    auto ret = merge(getBasisLca(x, lc), getBasisLca(y, lc));
    ret.insertVector(A[lc]);
    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int N; cin >> N;
  vector<int> A(N);
  F0R(i, N) {
    cin >> A[i];
  }

  Tree tree(N, A);
  REP(N-1) {
    int a, b; cin >> a >> b;
    a--, b--;
    tree.add_edge(a, b);
  }
  tree.init();

  int Q; cin >> Q;
  while (Q--) {
    int x, y, k; cin >> x >> y >> k;
    x--, y--;
    auto xb = tree.getBasis(x, y);
    cout << (!xb.insertVector(k) ? "YES" : "NO") << '\n';
  }
}
