#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2505;
int N, M, P;
struct Edge
{
    int to, wt;
};

vector<Edge> adj[maxn];
vector<Edge> rev[maxn];

bool vis2[maxn], vis0[maxn], vis[maxn];

void dfs(int i) {
    vis2[i] = true;
    for (auto e: rev[i]) {
        if (vis2[e.to]) continue;
        dfs(e.to);
    }
}

void dfs2(int i) {
    vis0[i] = true;
    vis[i] = vis2[i];
    for (auto e: adj[i]) {
        if (vis0[e.to]) continue;
        dfs2(e.to);
    }
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> P;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b,P-c});
        rev[b].push_back({a,P-c});
    }
    dfs(N);
    dfs2(1);
    for (int i = 1; i <= N; i++) {
        cout << i << ": " << vis[i] << '\n';
    }
    //bellman-ford
    vector<int> dist(N+1,2e9);
    dist[1] = 0;
    for (int i = 0; i < N - 1; i++) {
        for (int u = 1; u <= N; u++) {
            if (!vis[u]) continue;
            for (Edge& e: adj[u]) {
                int v = e.to;
                if (!vis[v]) continue;
                int wt = e.wt;
                if (dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }
    }
    bool hasNegCycle = false;
    //check for negative-weight
    for (int u = 1; u <= N; u++) {
        if (!vis[u]) continue;
        for (Edge& e: adj[u]) {
            int v = e.to;
            if (!vis[v]) continue;
            int wt = e.wt;
            if (dist[u] + wt < dist[v]) {
                /*
                cout << u << '\n';
                cout << dist[u] << ' ' << wt << ' ' << dist[v] << '\n';
                */
                hasNegCycle = true;
                break;
            }
        }
    }
    //output
    if (hasNegCycle) {
        cout << -1 << '\n';
    }
    else {
        cout << max(0,-dist[N]) << '\n';
    }
}

