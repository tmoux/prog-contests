#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N; cin >> N;
  using V = vector<vector<pair<int, int>>>;
  V adj(N);
  for (int i = 0; i < N-1; i++) {
    int a, b, w; cin >> a >> b >> w;
    a--, b--;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }
  vector<int> P(N);

  function<void(int, int, int)> dfs = [&](int i, int p, int c) {
    P[i] = c;
    for (auto [j, w]: adj[i]) if (j != p) {
      dfs(j, i, c^w);
    }
  };
  dfs(0, 0, 0);

  V v(1 << 20);
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      int x = P[i] ^ P[j];
      v[x].emplace_back(i, j);
      if (v[x].size() >= 2) {
        cout << v[x][0].first+1 << ' ' << v[x][0].second+1 << ' ' << v[x][1].first+1 << ' ' << v[x][1].second+1 << '\n';
        return;
      }
    }
  }
  cout << -1 << '\n';
}

int main() {
  int T; cin >> T;
  while (T--) solve();
}
