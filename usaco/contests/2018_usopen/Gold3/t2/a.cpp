#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  freopen("talent.in","r",stdin);
  freopen("talent.out","w",stdout);
  int N, W; cin >> N >> W;
  vector<int> w(N), t(N);
  for (int i = 0; i < N; i++) {
    cin >> w[i] >> t[i];
  }

  auto check = [N,W,&w,&t](int x) {
    const ll inf = 1e18;
    vector<ll> dp(W+1,-inf);
    dp[0] = 0;
    for (int i = 0; i < N; i++) {
      ll val = 1000LL*t[i]-1LL*x*w[i];
      for (int j = W; j >= 0; j--) {
        if (dp[j] == -inf) continue;
        int k = min(W,j+w[i]);
        dp[k] = max(dp[k],dp[j]+val);
      }
    }
    return dp[W] >= 0;
  };

  int lo = 0, hi = 1000 * 1000 * 250 + 1;
  while (lo + 1 < hi) {
    int mid = (lo+hi)/2;
    if (check(mid)) {
      lo = mid;
    }
    else {
      hi = mid;
    }
  }
  cout << lo << '\n';
}
