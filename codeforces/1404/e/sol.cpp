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

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

int N, M;
vector<string> g;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin >> N >> M;
  g.resize(N);
  F0R(i, N) cin >> g[i];
  int MX = 2 * N * M + 2;
  int source = MX - 2, sink = MX - 1;
  Dinic dinic(MX, source, sink);

  auto cv = [&](int i, int j) {
    return i * M + j;
  };
  F0R(i, N) {
    F0R(j, M) {
      if (i + 1 < N && j-1 >= 0 && g[i][j] == '#' && g[i+1][j] == '#' && g[i+1][j-1] == '#')
        dinic.add_edge(cv(i, j), cv(i+1, j-1) + N*M, 1);
      if (i + 1 < N && j-1 >= 0 && g[i][j] == '#' && g[i+1][j] == '#' && g[i][j-1] == '#')
        dinic.add_edge(cv(i, j), cv(i, j-1) + N*M, 1);
      if (i + 1 < N && j + 1 < M && g[i][j] == '#' && g[i+1][j] == '#' && g[i+1][j+1] == '#')
        dinic.add_edge(cv(i, j), cv(i+1, j) + N*M, 1);
      if (i + 1 < N && j + 1 < M && g[i][j] == '#' && g[i+1][j] == '#' && g[i][j+1] == '#')
        dinic.add_edge(cv(i, j), cv(i, j) + N*M, 1);
    }
  }
  F0R(i, N) {
    F0R(j, M) {
      dinic.add_edge(source, cv(i, j), 1);
      dinic.add_edge(cv(i, j) + N*M, sink, 1);
    }
  }

  int ans = 0;
  int V = 0;
  F0R(i, N) {
    F0R(j, M) {
      if (g[i][j] == '#') ans++;
      if (i + 1 < N && g[i][j] == '#' && g[i+1][j] == '#') {
        V++;
      }
      if (j + 1 < M && g[i][j] == '#' && g[i][j+1] == '#') {
        V++;
      }
    }
  }

  int vertex_cover = dinic.flow();
  int max_ind_set = V - vertex_cover;
  cout << (ans - max_ind_set) << '\n';
}
