#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1005;
const ll INF = 1e12;
int N, M, C;

ll dp[maxn][maxn];

vector<int> adj[maxn];
void amax(ll& a, ll b) {
  a = max(a,b);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  freopen("time.in","r",stdin);
  freopen("time.out","w",stdout);
  cin >> N >> M >> C;
  vector<int> m(N);
  for (auto& i: m) cin >> i;
  for (int i = 0; i < M; i++) {
    int a, b; cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
  }
  for (int i = 1; i < N; i++) {
    dp[i][0] = -INF;
  }
  dp[0][0] = 0;
  ll ans = 0;
  for (int t = 0; t < 1000; t++) {
    for (int i = 0; i < N; i++) {
      dp[i][t+1] = -INF;
    }
    ll dt = 1LL*C*(t*t-(t+1)*(t+1));
    for (int i = 0; i < N; i++) {
      for (int j: adj[i]) {
        amax(dp[j][t+1],dp[i][t]+m[j]+dt);
      }
    }
    ans = max(ans,dp[0][t+1]);
  }
  cout << ans << '\n';
}
