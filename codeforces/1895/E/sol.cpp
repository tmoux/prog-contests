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

void solve() {
  int N; cin >> N;
  vector<pair<int, int>> A(N);
  F0R(i, N) cin >> A[i].first;
  F0R(i, N) cin >> A[i].second;

  int M; cin >> M;
  vector<pair<int, int>> B(M);
  F0R(i, M) cin >> B[i].first;
  F0R(i, M) cin >> B[i].second;

  auto computeNext = [](vector<pair<int, int>> A, vector<pair<int, int>> B) -> vector<int> {
    vector<array<int, 3>> v;
    vector<int> nextA(sz(A));
    F0R(i, sz(B)) v.push_back({B[i].first, B[i].second, i});
    sort(all(v), [&](auto a, auto b) {
      return a[0] > b[0];
    });
    int i = 0;
    pair<int, int> best = {-1, -1}; // y, id

    vector<array<int, 3>> as;
    F0R(i, sz(A)) as.push_back({A[i].first, A[i].second, i});
    sort(all(as), [&](auto a, auto b) {
      return a[1] > b[1];
    });
    for (auto [x, y, id]: as) {
      while (i < sz(v) && v[i][0] > y) {
        ckmax(best, {v[i][1], v[i][2]});
        i++;
      }
      nextA[id] = best.second;
    }
    return nextA;
  };

  auto nextA = computeNext(A, B);
  auto nextB = computeNext(B, A);

  DirectedGraph graph(N + M);
  F0R(i, N) {
    // cout << i << ": " << nextA[i] << endl;
    if (nextA[i] != -1) {
      graph.add_edge(i, nextA[i] + N);
    }
  }
  F0R(i, M) {
    // cout << i << ": " << nextB[i] << endl;
    if (nextB[i] != -1) {
      graph.add_edge(i + N, nextB[i]);
    }
  }
  graph.init();
  auto [ngraph, compOf] = graph.createCondensationGraph();

  const int INV = -2;
  vector<int> ans(N + M, INV);
  auto F = y_combinator([&](auto F, int i) -> int {
    if (ans[i] != INV) return ans[i];
    if (graph.g[i].empty()) return ans[i] = i < N ? 1 : -1;
    else {
      assert(sz(graph.g[i]) == 1);
      int j = graph.g[i][0];
      if (compOf[i] == compOf[j]) return ans[i] = 0;
      else return ans[i] = F(j);
    }
  });

  int win = 0, loss = 0, draw = 0;
  F0R(i, N) {
    int x = F(i);
    if (x == 1) win++;
    else if (x == -1) loss++;
    else draw++;
  }

  cout << win << ' ' << draw << ' ' << loss << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
