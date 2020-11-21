#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50005;
int N, M, F, s, t;

vector<pair<int,ll>> adj[2*maxn];

ll dist[2*maxn];
void Dijkstra() {
	set<pair<ll,int>> setds;
	for (int i = 0; i < 2*N; i++) {
		dist[i] = 1e18;
	}
    dist[s] = 0;
    setds.insert({0,s});
	while (!setds.empty()) {
		int u = setds.begin()->second;
		setds.erase(setds.begin());
		for (const auto& e: adj[u]) {
			int v = e.first;
			ll weight = e.second;
			if (dist[v] > dist[u] + weight) {
				setds.erase({dist[u],u});
				dist[v] = dist[u] + weight;
				setds.insert({dist[v],v});
			}
		}
	}
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M >> F >> s >> t;
    for (int i = 0; i < M; i++) {
        int a, b, c; cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[a].push_back({b+N,c});
        adj[b].push_back({a,c});
        adj[b].push_back({a+N,c});

        adj[a+N].push_back({b+N,c});
        adj[b+N].push_back({a+N,c});
    }
    for (int i = 0; i < F; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back({v+N,0});
    }
    Dijkstra();
    cout << min(dist[t],dist[t+N]) << '\n';
}
