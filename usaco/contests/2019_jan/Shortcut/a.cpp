#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 10005, INF = 2e9+9;
int N, M, T;
int c[maxn];
struct Edge
{
	int to, weight;
};
vector<Edge> adj[maxn];

vector<int> dijkstra(int source) {
	vector<int> dist(N+1,INF);
	dist[source] = 0;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	pq.push({0,source});
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		for (Edge& e: adj[u]) {
			int v = e.to;
			int weight = e.weight;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				pq.push({dist[v],v});
			}
		}
	}
	return dist;
}

vector<int> t_edge[maxn];
int total[maxn];
int dfs(int i, int p) {
	total[i] = c[i];
	for (int j: t_edge[i]) {
		if (j == p) continue;
		total[i] += dfs(j,i);
	}
	return total[i];
}

int main()
{
	freopen("shortcut.in","r",stdin); freopen("shortcut.out","w",stdout);
	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		cin >> c[i];
	}
	for (int i = 1; i <= M; i++) {
		int u, v, w; cin >> u >> v >> w;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	vector<int> dist = dijkstra(1);
	for (int i = 2; i <= N; i++) {
		int best = N + 1;
		for (Edge& e: adj[i]) {
			if (dist[i] == dist[e.to] + e.weight) {
				best = min(best,e.to);
			}
		}
		t_edge[i].push_back(best);
		t_edge[best].push_back(i);
		//cout << i << ": " << best << '\n';
	}
	dfs(1,1); //get how many cows pass through this node
	ll ans = 0;
	for (int i = 2; i <= N; i++) {
		ll r = 1LL * total[i] * (dist[i] - T);
		ans = max(ans,r);
	}
	cout << ans << '\n';
}