#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 150005;
const ll INF = 1e18;
int N, M, F, s, t;
struct Edge
{
	int to, weight;
};
vector<Edge> adj[2*maxn];

vector<ll> dijkstra(int source) {
	vector<ll> dist(2*N,INF);
	dist[source] = 0;
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
	pq.push({0LL,source});
	while (!pq.empty()) {
		int u = pq.top().second; 
        int d = pq.top().first;
		pq.pop();
        if (d > dist[u]) continue; 
		for (Edge& e: adj[u]) {
			int v = e.to;
			ll weight = e.weight;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				pq.push({dist[v],v});
			}
		}
	}
	return dist;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> F >> s >> t;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        adj[a+N].push_back({b+N,c});
        adj[b+N].push_back({a+N,c});
    }
    for (int i = 0; i < F; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back({b+N,0});
    }
    auto dist = dijkstra(s);
    cout << min(dist[t],dist[t+N]) << '\n';
}
