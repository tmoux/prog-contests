#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> deg(n,0);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
      int u, v; cin >> u >> v;
      --u; --v;
      ++deg[u]; ++deg[v];
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    vector<int> cycle(n,1);
    queue<int> q;
    for (int i = 0; i < n; i++) {
      if (deg[i] == 1) {
        q.push(i);
      }
    }
    while (!q.empty()) {
      int f = q.front(); q.pop();
      cycle[f] = 0;
      for (int j: adj[f]) {
        if (--deg[j] == 1) {
          q.push(j);
        }
      }
    }
    vector<int> cyc;
    for (int i = 0; i < n; i++) if (cycle[i]) cyc.push_back(i);
    vector<int> sz(n);
    function<int(int,int)> dfs = [&dfs,&adj,&cycle,&sz](int i, int p) -> int {
      sz[i] = 1;
      for (int j: adj[i]) {
        if (!cycle[j] && j != p) {
          sz[i] += dfs(j,i);
        }
      }
      return sz[i];
    };
    ll ans = 0;
    for (int i: cyc) {
      dfs(i,i);
      ll a = sz[i]-1;
      ll b = (n-1)-a;
      ans += sz[i]*(a + 2*b);
    }
    ans /= 2;
    cout << ans << '\n';
  }
}
