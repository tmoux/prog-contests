#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 31*31;
int n, m, c;
char grid[33][33];
int cost[30];

const ll INF = 1e18;

int dx[] = {0,-1,0,1};
int dy[] = {1,0,-1,0};

ll cap[2*maxn][2*maxn];
bool visited[2*maxn];

bool valid(int i, int j) {
    return 0 <= i && i < m && 0 <= j && j < n;
}
int cv(int i, int j) {
    return i*n + j;
}

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

int main() {
    cin >> n >> m >> c;
    pair<int,int> start;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'B') {
                start = {i,j};
            }
        }
    }
    for (int i = 0; i < c; i++) {
        cin >> cost[i];
    }
    Dinic graph = Dinic(2*n*m+1,cv(start.first,start.second),2*n*m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            //add in -> out. INF if B or . else cost[char]
            if (grid[i][j] == '.' || grid[i][j] == 'B') {
                graph.add_edge(cv(i,j),cv(i,j)+n*m,INF);
            }
            else {
                graph.add_edge(cv(i,j),cv(i,j)+n*m,cost[grid[i][j]-'a']);
            }
            //add out -> adjacent (in)
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (valid(ni,nj)) {
                    graph.add_edge(cv(i,j)+n*m,cv(ni,nj),INF);
                }
            }
            //connect boundaries to sink
            if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                graph.add_edge(cv(i,j)+n*m,2*n*m,INF);
            }
        }
    }

    ll ans = graph.flow();
    cout << (ans >= 1e18 ? -1 : ans) << '\n';
}

