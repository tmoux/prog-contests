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


int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N; cin >> N;
  DirectedGraph graph(N);
  vector<int> P(N);
  F0R(i, N) {
    cin >> P[i];
    P[i]--;
    graph.add_edge(i, P[i]);
  }

  auto [ng, compOf] = graph.createCondensationGraph();
  vector<int> compSize(ng.n);
  F0R(i, N) {
    compSize[compOf[i]]++;
  }
  vector<int> inCycle(N);
  int numNotInCycle = 0;
  F0R(i, N) {
    inCycle[i] = compSize[compOf[i]] > 1 || P[i] == i;
    if (!inCycle[i]) numNotInCycle++;
  }

  pair<int, int> change = {-1, -1};
  if (numNotInCycle == 0) {
    // all already in a cycle, don't change anything
    change = {0, P[0]};
  }
  else {
    // find longest path in the tree
    vector<int> par(N);
    pair<int, int> mx = {-1, -1};
    auto dfs = y_combinator([&](auto dfs, int i, int p, int d) -> void {
      par[i] = p;
      ckmax(mx, {d, i});
      for (int j: graph.gr[i]) {
        dfs(j, i, d+1);
      }
    });
    F0R(i, N) {
      if (!inCycle[i] && inCycle[P[i]]) {
        dfs(i, P[i], 0);
      }
    }
    int j = mx.second;
    vector<int> chain;
    while (!inCycle[j]) {
      chain.push_back(j);
      j = par[j];
    }
    P[chain.back()] = chain.front();
    change = {chain.back(), chain.front()};
    int len = sz(chain);
    for (auto i: chain) {
      inCycle[i] = 1;
      compSize[compOf[i]] = len;
    }
  }
  assert(change.first != -1);

  // Part 2: Find study groups
  const int MX = 20;
  vector<vector<int>> jmp(MX, vector<int>(N));
  F0R(i, N) jmp[0][i] = P[i];
  for (int k = 1; k < MX; k++) {
    F0R(i, N) {
      jmp[k][i] = jmp[k-1][jmp[k-1][i]];
    }
  }
  auto jump = [&](int i, int x) -> int {
    F0Rd(k, MX) {
      if (x & (1 << k)) {
        i = jmp[k][i];
      }
    }
    return i;
  };
  vector<int> compress(N);
  int c = 1;
  F0R(i, N) {
    if (inCycle[i]) {
      compress[i] = c++;
    }
  }
  vector<int> group(N);
  F0R(i, N) {
    int p = jump(i, N);
    assert(inCycle[p]);
    int len = compSize[compOf[p]];
    int j = jump(i, len * ((N / len) + 1));
    assert(inCycle[j]);

    group[i] = compress[j];
  }

  // output
  cout << change.first+1 << ' ' << change.second+1 << '\n';
  F0R(i, N) {
    cout << group[i] << " \n"[i == N-1];
  }
}
