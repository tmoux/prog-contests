#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Template {{{
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
// }}}

pair<int, int> mincomp(pair<int, int> x, pair<int, int> y) {
  return min(x, y);
}

// combine should be associative and idempotent (e.g., min, max, gcd)
template<typename T, T (*combine)(T, T)>
struct SparseTable
{
  int n, maxk;
  vector<vector<T>> tb;
  static inline int lg(int x) { return 32 - __builtin_clz(x) - 1; }
  SparseTable() {}
  SparseTable(const vector<T>& a) : n(sz(a)) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    tb.resize(maxk, vector<T>(n));
    for (int i = 0; i < n; i++) tb[0][i] = a[i];
    for (int k = 1; k <= lg(n); k++) {
      for (int i = 0; i < n; i++) {
        int nx = i + (1<<(k-1));
        if (nx < n) tb[k][i] = combine(tb[k-1][i],tb[k-1][nx]);
        else tb[k][i] = tb[k-1][i];
      }
    }
  }
  T prod(int l, int r) {
    int g = lg(r-l+1);
    return combine(tb[g][l],tb[g][r-(1<<g)+1]);
  }
};

// Data structure for handling LCA queries
struct Tree {
  int n, maxk;
  bool is_0_index;
  vector<vector<int>> adj;
  vector<int> depth;
  vector<pair<int, int>> E;
  vector<int> Eindex;
  int e_idx = 0;
  SparseTable<pair<int, int>, mincomp> table;

  void dfs(int i, int p, int& t) {
    depth[i] = p == -1 ? 0 : depth[p] + 1;
    Eindex[i] = e_idx;
    E[e_idx++] = {depth[i], i};
    for (int j: adj[i]) {
      if (j != p) {
        dfs(j, i, t);
        E[e_idx++] = {depth[i], i};
      }
    }
  }

  Tree(int _n, bool _is_0_index = true) : n(_n), is_0_index(_is_0_index) {
    maxk = 0;
    while (n >= (1<<maxk)) maxk++;
    int sz = is_0_index ? n : n+1;
    adj.resize(sz);
    depth.resize(sz, 0);
    E.resize(2*sz-1);
    Eindex.resize(sz, -1);
    e_idx = 0;
  }
  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void init() {
    int root = is_0_index ? 0 : 1;
    int t = 0;
    dfs(root, -1, t);
    table = SparseTable<pair<int, int>, mincomp>(E);
  }

  int lca(int a, int b) {
    int i = Eindex[a], j = Eindex[b];
    if (i > j) swap(i, j);
    return table.prod(i, j).second;
  }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, Q; cin >> N >> Q;
  Tree tree(N);
  FOR(i, 1, N) {
    int p; cin >> p;
    tree.add_edge(p, i);
  }
  tree.init();

  REP(Q) {
    int u, v; cin >> u >> v;
    cout << tree.lca(u, v) << '\n';
  }
}
