#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge
{
    int from, to, capacity, cost;
};

vector<vector<int>> adj, cost, capacity;
const int INF = 1e9;
void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n,INF);
    d[v0] = 0;
    vector<bool> inq(n,false);
    queue<int> q;
    q.push(v0);
    p.assign(n,-1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v: adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N,vector<int>());
    cost.assign(N,vector<int>(N,0));
    capacity.assign(N,vector<int>(N,0));
    for (Edge e: edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF) {
            break;
        }

        //find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f,capacity[p[cur]][cur]);
            cur = p[cur];
        }

        //apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else return cost;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k; cin >> n >> k;
    int source = 0, sink = 2*n+3;
    int N = sink+1;
    vector<Edge> edges;
    for (int i = 1; i <= n; i++) {
        for (int j = i+1; j <= n+1; j++) {
            int ci; cin >> ci;
            edges.push_back({i,j+n+1,1,ci});
        }
    }
    for (int i = 1; i <= n; i++) {
        if (i == 1) edges.push_back({source,i,k,0});
        else edges.push_back({source,i,1,0});
    }
    for (int i = 2; i <= n+1; i++) {
        edges.push_back({i+n+1,sink,1,0});
    }
    int ans = min_cost_flow(N,edges,n,source,sink);
    cout << ans << '\n';
}

