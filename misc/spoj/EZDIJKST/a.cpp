#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005;
const int INF = 2e9+9;
typedef pair<int,int> edge;
vector<edge> adj[maxn];

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int v, k; cin >> v >> k;
        for (int i = 1; i <= v; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < k; i++) {
            int a, b, t; cin >> a >> b >> t;
            adj[a].push_back({t,b});
        }
        int source, sink; cin >> source >> sink;
        vector<int> dist(v+1,INF);
        priority_queue<edge,vector<edge>,greater<edge>> pq;
        pq.push({0,source});
        dist[source] = 0;
        while (!pq.empty()) {
            int u = pq.top().second; pq.pop();
            for (edge e: adj[u]) {
                int v = e.second;
                int weight = e.first;
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v],v});
                }
            }
        }
        cout << (dist[sink] == INF ? "NO" : to_string(dist[sink])) << '\n';
    }

    return 0;
}
