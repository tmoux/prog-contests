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

const int maxn = 1e5+5, maxd = 55;
int N, M, D;
int A[maxn][maxd];

struct DSU {
  int n;
  vector<int> par;
  vector<int> score;
  DSU(int _n) {
    n = _n;
    par.resize(n, -1);
    score.resize(n, 0);
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

int cv(int i, int d) {
  return i*D + d;
}
pair<int, int> vc(int i) {
  return {i / D, i % D};
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M >> D;
  DirectedGraph graph(N);
  REP(M) {
    int a, b; cin >> a >> b;
    a--, b--;
    graph.add_edge(a, b);
  }
  graph.init();
  F0R(i, N) {
    F0R(j, D) {
      char c; cin >> c;
      A[i][j] = c - '0';
    }
  }

  auto [ng, compOf] = graph.createCondensationGraph();
  DSU dsu(N * D);
  F0R(i, N) {
    F0R(d, D) {
      for (int j: graph.g[i]) {
        if (compOf[i] == compOf[j]) {
          dsu.Union(cv(i, d), cv(j, (d+1)%D));
        }
      }
    }
  }

  int n = ng.n;
  vector<vector<int>> comp(n);
  F0R(i, N) comp[compOf[i]].push_back(i);


  vector<bool> cur(N), vis(N * D);
  F0Rd(c, n) {
    for (int i: comp[c]) {
      F0R(d, D) {
        int id1 = dsu.Find(cv(i, d));
        for (int j: graph.g[i]) {
          if (compOf[i] != compOf[j]) {
            int id2 = dsu.Find(cv(j, (d+1)%D));
            ckmax(dsu.score[id1], dsu.score[id2]);
          }
        }
      }
    }
    vector<int> v;
    auto bfs = [&](int f, int& cnt) -> void {
      queue<int> q;
      q.push(f);
      while (!q.empty()) {
        int i = q.front(); q.pop();
        if (!vis[i]) {
          vis[i] = 1;
          auto [ii, d] = vc(i);
          if (!cur[ii] && A[ii][d]) {
            cur[ii] = 1;
            cnt++;
            v.push_back(ii);
          }
          for (int j: graph.g[ii]) {
            if (compOf[ii] == compOf[j]) {
              q.push(cv(j, (d+1)%D));
            }
          }
        }
      }
    };

    for (int i: comp[c]) {
      F0R(d, D) {
        int id = dsu.Find(cv(i, d));
        if (id == cv(i, d)) {
          int cnt = 0;
          bfs(cv(i, d), cnt);
          dsu.score[id] += cnt;

          for (int j: v) cur[j] = 0;
          v.clear();
        }
      }
    }
  }

  cout << dsu.score[dsu.Find(cv(0, 0))] << '\n';
}
