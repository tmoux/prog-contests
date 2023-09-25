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

struct DirectedGraph {
#define trav(a, x) for (auto &a : x)
  using vi = vector<int>;
  int n;
  vector<vi> g, gr;
  vector<bool> used;
  vi ord, comp;

  vi compOf;
  int nc;

  vi indegree, source;

  DirectedGraph(int _n) : n(_n) {
    nc = 0;
    compOf = vi(n);
    g = vector<vi>(n);
    gr = vector<vi>(n);
    indegree = vi(n);
    source = vi(n);
  }

  void add_edge(int i, int j) {
    g[i].push_back(j);
    gr[j].push_back(i);
  }

  void init() {
    F0R(i, n) {
      sort(all(g[i])); g[i].erase(unique(all(g[i])), g[i].end());
      sort(all(gr[i])); gr[i].erase(unique(all(gr[i])), gr[i].end());
    }
    F0R(i, n) {
      for (int j: g[i]) {
        ++indegree[j];
      }
    }
    F0R(i, n) source[i] = indegree[i] == 0;
  }

  void dfs1(int v) {
    used[v] = true;
    for (auto a: g[v]) {
      if (!used[a]) dfs1(a);
    }
    ord.push_back(v);
  }

  void dfs2(int v) {
    used[v] = true;
    comp.push_back(v);
    for (auto a: gr[v]) {
      if (!used[a]) dfs2(a);
    }
  }

  void findSCCs() {
    ord.clear();
    used.assign(n, false);
    F0R(i, n) {
      if (!used[i]) dfs1(i);
    }
    used.assign(n, false);
    F0R(i, n) {
      int v = ord[n-1-i];
      if (!used[v]) {
        dfs2(v);
        trav(a, comp) {
          compOf[a] = nc;
        }
        nc++;
        comp.clear();
      }
    }
  }

  pair<DirectedGraph, vi> createCondensationGraph() {
    findSCCs();
    DirectedGraph ret(nc);
    F0R(i, n) {
      int c = compOf[i];
      for (int j: g[i]) {
        int d = compOf[j];
        if (c != d) {
          ret.add_edge(c, d);
        }
      }
    }
    ret.init();
    return {ret, compOf};
  }
};

void yes() {
  cout << "Yes\n";
  exit(0);
}

void no() {
  cout << "No\n";
  exit(0);
}

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

  bool Union(int x, int y) { // return true if x and y were not connected
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
  int N, M; cin >> N >> M;
  vector<array<int, 4>> v;
  REP(M) {
    int a, b, c, d; cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
    if (a == c) {
      if (b < d) continue;
      else no();
    }
    else {
      v.push_back({a, b, c, d});
    }
  }
  DSU dsu(N);
  while (1) {
    DirectedGraph graph(N);

    for (auto& [a, b, c, d]: v) {
      while (a <= b && c <= d && dsu.Find(a) == dsu.Find(c)) {
        a++, c++;
      }
      if (c > d) no();
      else if (a > b) continue;
      graph.add_edge(dsu.Find(a), dsu.Find(c));
    }
    auto [ngraph, compOf] = graph.createCondensationGraph();
    vector<vector<int>> comps(N);
    bool has_cycle = false;
    F0R(i, N) {
      comps[compOf[i]].push_back(i);
      if (sz(comps[compOf[i]]) > 1) has_cycle = true;
    }

    bool change = false;
    for (const auto& c: comps) {
      for (int i = 1; i < sz(c); i++) {
        if (dsu.Union(c[i], c[0])) change = true;
      }
    }

    if (!has_cycle) yes();
  }
}
