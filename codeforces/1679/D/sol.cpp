#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M;
  ll K;
  cin >> N >> M >> K;
  vector<int> A(N);
  vector<pair<int,int>> edges;
  for (auto& x: A) cin >> x;
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    a--; b--;
    edges.push_back({a, b});
  }

  auto check = [&](int x) -> bool {
    vector<vector<int>> adj(N);
    vector<int> indegree(N);
    for (auto [a, b]: edges) {
      if (max(A[a], A[b]) <= x) {
        adj[a].push_back(b);
        indegree[b]++;
      }
    }
    queue<int> q;
    for (int i = 0; i < N; i++) {
      if (indegree[i] == 0) {
        q.push(i);
      }
    }
    vector<int> v;
    while (!q.empty()) {
      int i = q.front(); q.pop();
      v.push_back(i);
      for (int j: adj[i]) {
        if (--indegree[j] == 0) {
          q.push(j);
        }
      }
    }

    if (static_cast<int>(v.size()) == N) {
      reverse(v.begin(), v.end());
      vector<int> path(N);
      for (int i: v) {
        if (A[i] > x) continue;
        path[i] = 1;
        for (int j: adj[i]) {
          path[i] = max(path[i], 1 + path[j]);
        }
      }
      return *max_element(path.begin(), path.end()) >= K;
    }
    else {
      return true;
    }
  };

  const int INF = 1e9+1;
  int lo = 0, hi = INF;
  while (lo + 1 < hi) {
    int mid = (lo+hi)/2;
    (check(mid) ? hi : lo) = mid;
  }
  cout << (hi < INF ? hi : -1) << '\n';
}
