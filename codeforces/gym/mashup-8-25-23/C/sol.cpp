#include <bits/stdc++.h>
using namespace std;
#define F0R(i, a) for (int i=0; i<(a); i++)

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int N, M; cin >> N >> M;
  vector<vector<int>> adj(N);
  vector<int> indegree(N);
  F0R(i, M) {
    int a, b; cin >> a >> b; a--, b--;
    swap(a, b);
    adj[a].push_back(b);
    adj[b].push_back(a);
    indegree[b]++;
  }
  priority_queue<int> pq;
  F0R(i, N) if (!indegree[i]) pq.push(i);

  vector<int> ans(N);
  int cnt = N;
  while (!pq.empty()) {
    auto i = pq.top(); pq.pop();
    ans[i] = cnt--;
    for (auto j: adj[i])
      if (--indegree[j] == 0) pq.push(j);
  }

  F0R(i, N) cout << ans[i] << ' ';
  cout << '\n';
}
