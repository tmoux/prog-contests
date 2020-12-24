#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e5+5;
int n, m;

vector<pair<int,ll>> adj[maxn];
vector<int> adj2[maxn];

ll dist[maxn];
void Dijkstra(int s) {
	set<pair<ll,int>> setds;
	for (int i = 0; i < n; i++) {
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
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int a, b, d; cin >> a >> b >> d;
    adj[a].push_back({b,d});
    adj[b].push_back({a,d});
  }
  Dijkstra(1);
  for (int i = 0; i < n; i++) {
    for (auto e: adj[i]) {
      int j = e.first;
      ll d = e.second;
      if (dist[i] != dist[j] + d) {
        adj2[i].push_back(j);
      }
    }
  }
  vector<int> par(n,-1);
  queue<int> q; q.push(0);
  par[0] = 0;
  while (!q.empty()) {
    int f = q.front(); q.pop();
    for (int j: adj2[f]) {
      if (par[j] == -1) {
        par[j] = f;
        q.push(j);
      }
    }
  }
  if (par[1] == -1) {
    cout << "impossible\n";
  }
  else {
    vector<int> ans;
    int i = 1;
    while (true) {
      ans.push_back(i);
      if (i == 0) break;
      i = par[i];
    }
    /*
    for (int i = 0; i < n; i++) {
      cout << i << ": " << par[i] << '\n';
    }
    return 0;
    */
    reverse(ans.begin(),ans.end());
    cout << ans.size() << ' ';
    for (auto i: ans) {
      cout << i << ' ';
    }
    cout << '\n';
  }
}
