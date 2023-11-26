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
  int M; cin >> M;
  vector<ll> A(N);
  F0R(i, N) cin >> A[i];

  DirectedGraph graph(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    graph.add_edge(a, b);
  }

  auto [ngraph, compOf] = graph.createCondensationGraph();
  int n = ngraph.n;
  vector<pair<int, ll>> W(n); // size, total weight
  F0R(i, N) {
    int c = compOf[i];
    W[c].first++;
    W[c].second += A[i];
    // cout << i << ": " << c << endl;
  }

  auto update = [&](pair<int, ll>& a, pair<int, ll> b) {
    if (b.first > a.first || (b.first == a.first && b.second < a.second)) {
      a = b;
    }
  };
  auto sum = [&](pair<int, ll> a, pair<int, ll> b) -> pair<int, ll> {
    return {a.first + b.first, a.second + b.second};
  };

  vector<pair<int, ll>> dp(n);
  pair<int, ll> ans = {0, 0};
  F0R(i, n) {
    update(dp[i], W[i]);
    update(ans, dp[i]);
    for (int j: ngraph.g[i]) {
      update(dp[j], sum(dp[i], W[j]));
    }
  }
  cout << ans.first << ' ' << ans.second << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int T; cin >> T;
  while (T--) solve();
}
