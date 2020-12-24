#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 505, INF = 999;
int a[maxn];
int dp[maxn][maxn][maxn];
int n;

void amin(int& a, int b) {
  a = min(a,b);
}

int f(int i, int j, int x) {
  int& res = dp[i][j][x];
  if (res != -1) return res;
  if (i == n) return res = 0;
  if (a[i] < j) {
    if (x < j) {
      return res = INF;
    }
    else {
      if (a[i] > x) {
        return res = 1+f(i+1,x,a[i]);
      }
      else {
        return res = INF;
      }
    }
  }
  else {
    res = f(i+1,a[i],x);
    if (a[i] > x && x >= j) {
      amin(res,1+f(i+1,x,a[i]));
    }
    return res;
  }
}
void solve() {
  int x; cin >> n >> x;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= 500; j++) {
      for (int k = 0; k <= 500; k++) {
        dp[i][j][k] = -1;
      }
    }
  }
  int ans = f(0,0,x);
  cout << (ans>=INF?-1:ans) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    solve();
  }
}
