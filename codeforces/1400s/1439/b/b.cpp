#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

void solve() {
  int n, m, k; cin >> n >> m >> k;
  vector<gp_hash_table<int,bool>> adj(n+1);
  vector<int> deg(n+1);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u][v] = 1;
    adj[v][u] = 1;
    ++deg[u];
    ++deg[v];
  }

  if (k > 450) {
    cout << -1 << '\n';
    return;
  }

  auto remove_vert = [&adj](int i) {
    for (auto p: adj[i]) {
      int j = p.first;
      adj[j].erase(i);
    }
    adj[i].clear();
  };

  auto is_clique = [&adj](vector<int>& v) {
    for (int i = 0; i < (int)v.size(); i++) {
      for (int j = i+1; j < (int)v.size(); j++) {
        if (adj[v[i]].find(v[j]) == adj[v[i]].end()) return false;
      }
    }
    return true;
  };

  set<pair<int,int>> s;
  for (int i = 1; i <= n; i++) s.insert({deg[i],i});
  while (!s.empty()) {
    auto f = *s.begin(); 
    int d = f.first;
    int i = f.second;
    if (d >= k) break;
    else if (d == k-1) {
      vector<int> v = {i};
      for (auto p: adj[i]) v.push_back(p.first);
      //cout << i << ": " << d << ' ' << adj[i].size() << endl;
      assert((int)v.size() == k);
      if (is_clique(v)) {
        cout << 2 << '\n';
        for (auto j: v) {
          cout << j << ' ';
        }
        cout << '\n';
        return;
      }
    }
    s.erase(s.begin());
    for (auto p: adj[i]) {
      int j = p.first;
      if (s.count({deg[j],j})) {
        s.erase({deg[j],j});
        --deg[j];
        s.insert({deg[j],j});
      }
    }
    remove_vert(i);
  }
  if (!s.empty()) {
    cout << 1 << ' ' << s.size() << '\n';
    for (auto i: s) {
      cout << i.second << ' ';
    }
    cout << '\n';
    return;
  }
  else {
    cout << -1 << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
