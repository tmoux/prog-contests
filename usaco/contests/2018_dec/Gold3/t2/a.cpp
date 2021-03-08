#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  freopen("teamwork.in","r",stdin);
  freopen("teamwork.out","w",stdout);
  int N, K; cin >> N >> K;
  vector<int> a(N);
  for (auto& i: a) cin >> i;
  vector<int> dp(N);
  for (int i = 0; i < N; i++) {
    int mx = 0;
    for (int j = i, sz = 1; j >= 0 && sz <= K; j--, sz++) {
      mx = max(mx,a[j]);
      dp[i] = max(dp[i],(j==0?0:dp[j-1])+mx*sz);
    }
  }
  cout << dp[N-1] << '\n';
}
