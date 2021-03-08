#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  freopen("superbull.in","r",stdin);
  freopen("superbull.out","w",stdout);
  int N; cin >> N;
  vector<int> a(N);
  for (auto& i: a) cin >> i;
  vector<vector<int>> g(N,vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      g[i][j] = a[i] ^ a[j];
    }
  }
  ll ans = 0;
  vector<int> dist(N);
  vector<bool> in(N,false);
  in[0] = true;
  for (int i = 0; i < N; i++) {
    dist[i] = g[0][i];
  }
  for (int _ = 0; _ < N-1; _++) {
    pair<int,int> nxt = {-1,-1};
    for (int i = 0; i < N; i++) if (!in[i]) {
      nxt = max(nxt,{dist[i],i});
    }
    assert(nxt.second != -1);
    int j = nxt.second;
    ans += nxt.first;
    in[j] = true;
    for (int i = 0; i < N; i++) {
      dist[i] = max(dist[i],g[j][i]);
    }
  }
  cout << ans << '\n';
}
