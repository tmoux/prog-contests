#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void amin(int& a, int b) {
  a = min(a,b);
}
const int maxn = 3005;
int n;
int a[maxn];
int dp[maxn][maxn];
const int INF = 5005;
int pfx[maxn][maxn];
void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int j = 1; j < n; j++) {
    for (int i = 0; i < n; i++) {
      pfx[j][i] = i+a[i] >= j;
      if (i > 0) pfx[j][i] += pfx[j][i-1];
    }
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      dp[i][j] = i==n-1?0:INF;
    }
  }
  for (int i = n-2; i >= 0; i--) {
    for (int j = i+1; j < n; j++) {
      int zsum = pfx[j][j-1]-pfx[j][i];
      if (j <= i+a[i]) {
        amin(dp[i][j],zsum+dp[j][i+a[i]+1]);
      }
    }
    for (int k = n-1; k >= i+1; k--) {
      amin(dp[i][k],dp[i][k+1]);
    }
  }
  cout << dp[0][1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
