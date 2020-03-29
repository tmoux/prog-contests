#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define pb push_back
#define sz(x) (int)x.size()

const int maxn = 505;
int n, m;
set<int> adj[maxn];
int deg[maxn];

/**
 * Description: Fast flow. After computing flow, edges $$${u,v}$$$ such that 
    * $$$level[u] \neq -1,$$$ $$$level[v] = -1$$$ are part of min cut.
 * Time: $$$O(N^2M)$$$ flow, $$$O(M\sqrt N)$$$ bipartite matching
 * Source: GeeksForGeeks, Chilli
 * Verification: RMI 2017 Day 1 Fashion
    * https://pastebin.com/VJxTvEg1
 */

template<int SZ> struct Dinic {
    typedef int F; // flow type
    struct Edge { int to, rev; F flow, cap; };
    int N,s,t;
    vector<Edge> adj[SZ];
    typename vector<Edge>::iterator cur[SZ];
    void ae(int u, int v, F cap) {
        assert(cap >= 0); // don't try smth dumb
        Edge a{v, adj[v].size(), 0, cap}, b{u, adj[u].size(), 0, 0};
        adj[u].pb(a), adj[v].pb(b);
    }
    int level[SZ];
    bool bfs() { // level = shortest distance from source
        for (int i = 0; i < N; i++) level[i] = -1, cur[i] = begin(adj[i]);
        queue<int> q({s}); level[s] = 0; 
        while (sz(q)) {
            int u = q.front(); q.pop();
            for (auto e: adj[u]) if (level[e.to] < 0 && e.flow < e.cap) 
                q.push(e.to), level[e.to] = level[u]+1;
        }
        return level[t] >= 0;
    }
    F sendFlow(int v, F flow) {
        if (v == t) return flow;
        for (; cur[v] != end(adj[v]); cur[v]++) {
            Edge& e = *cur[v];
            if (level[e.to]!=level[v]+1||e.flow==e.cap) continue;
            auto df = sendFlow(e.to,min(flow,e.cap-e.flow));
            if (df) { // saturated at least one edge
                e.flow += df; adj[e.to][e.rev].flow -= df;
                return df;
            }
        }
        return 0;
    }
    F maxFlow(int NN, int _s, int _t) {
        N = NN, s = _s, t = _t; if (s == t) return -1;
        F tot = 0;
        while (bfs()) while (auto df = sendFlow(s,
            numeric_limits<F>::max())) tot += df;
        return tot;
    }
};

bool link[maxn][maxn];

struct BipartiteMatcher {
  vector<vector<int>> G;
  vector<int> L, R, Viz;
  
  BipartiteMatcher(int n, int m) :
  G(n), L(n, -1), R(m, -1), Viz(n) {}
  
  void AddEdge(int a, int b) {
    G[a].push_back(b);
  }
  
  bool Match(int node) {
    if (Viz[node])
      return false;
    Viz[node] = true;
    
    for (auto vec : G[node]) {
      if (R[vec] == -1) {
        L[node] = vec;
        R[vec] = node;
        return true;
      }
    }
    
    for (auto vec : G[node]) {
      if (Match(R[vec])) {
        L[node] = vec;
        R[vec] = node;
        return true;
      }
    }
    
    return false;
  }
  
  int Solve() {
    int ok = true;
    while (ok--) {
      fill(Viz.begin(), Viz.end(), 0);
      for (int i = 0; i < (int)L.size(); ++i)
        if (L[i] == -1)
          ok |= Match(i);
    }
    
    int ret = 0;
    for (int i = 0; i < L.size(); ++i)
      ret += (L[i] != -1);
    return ret;
  }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].insert(v);
        ++deg[v];
        link[u][v] = 1;
    }
    /*
    for (int k = 0; k < n; k++) {
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                link[a][b] |= link[a][k] & link[k][b];
            }
        }
    }
    */
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) q.push(i);
    }
    set<int> v;
    while (!q.empty()) {
        int f = q.front(); q.pop();
        v.insert(f);
        for (int j: adj[f]) {
            if (--deg[j] == 0) {
                q.push(j);
            }
        }
    }
    for (int i = 0; i < n; i++) if (!v.count(i)) {
        for (int j = 0; j < n; j++) {
            link[i][j] = link[j][i] = 0;
        }
    }
    auto g = BipartiteMatcher(n,n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (link[i][j]) g.AddEdge(i,j);
        }
    }
    cout << v.size()-g.Solve() << '\n';
    /*
    Dinic<1005> D;
    int src = 2*n, sink = 2*n+1;
    for (int i = 0; i < n; i++) {
        D.ae(src,i,1);
        D.ae(i+n,sink,1);
        for (int j = 0; j < n; j++) {
            if (link[i][j]) {
                //cout << i << ' ' << j << '\n';
                D.ae(i,j+n,1);
            }
        }
    }
    int flow = D.maxFlow(2*n+2,src,sink);
    int ans = (int)v.size()-flow;
    cout << ans << '\n';
    */
}
