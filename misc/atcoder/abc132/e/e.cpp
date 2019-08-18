#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pp = pair<int,pair<int,int>>;

const int maxn = 1e5+5, INF = 2e9+9;
int N, M;
vector<int> adj[maxn];

int dist[maxn][3];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j < 3; j++) {
            dist[i][j] = INF;
        }
    }
    int S, T; cin >> S >> T;
    dist[S][0] = 0;
    priority_queue<pp,vector<pp>,greater<pp>> pq;
    pq.push({0,{S,0}});
    while (!pq.empty()) {
        auto p = pq.top().second;
        pq.pop();
        int u = p.first;
        int k = p.second;
        int nx = (k+1) % 3;
        for (int v: adj[u]) {
            if (dist[v][nx] > dist[u][k] + 1) {
                dist[v][nx] = dist[u][k] + 1;
                pq.push({dist[v][nx],{v,nx}});
            }
        }
    }
    if (dist[T][0] == INF) {
        cout << -1 << '\n';
    }
    else {
        cout << (dist[T][0]/3) << '\n';
    }
}

