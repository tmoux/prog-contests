#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  using pii = pair<int, int>;
  map<pii, int> mp;
  for (int i = 0; i < M; i++) {
    int u, v; cin >> u >> v;
    u--; v--;
    mp[{u, v}]++;
  }
  vector<vector<pii>> adj(N);
  for (auto [p, c]: mp) {
    auto [u, v] = p;
    adj[v].push_back({u, c});
  }
  vector<int> outdegree_sum(N);
  for (int i = 0; i < N; i++) {
    for (auto [j, w]: adj[i]) {
      outdegree_sum[j] += w;
    }
  }
  const int INF = 2e9;
  vector<int> dist(N, INF);
  dist[N-1] = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, N-1});
  while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;
    for (auto [v, w]: adj[u]) {
      outdegree_sum[v] -= w;
      if (dist[v] > dist[u] + outdegree_sum[v] + 1) {
        dist[v] = dist[u] + outdegree_sum[v] + 1;
        pq.push({dist[v], v});
      }
    }
  }
  cout << dist[0] << '\n';
}
