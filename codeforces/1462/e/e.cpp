#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5+5;

int n, m, k, a[maxn];
ll ch[maxn][105];
void solve() {
  //cin >> n >> m >> k;
  cin >> n;
  m = 3;
  k = 2;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a,a+n);
  ll ans = 0;
  int pt = 0;
  for (int i = 0; i < n; i++) {
    while (pt < n && a[pt] <= a[i]+k) {
      pt++;
    }
    //pt-i-1 choose m-1
    if (pt-i-1 >= 0) {
      ans += ch[pt-i-1][m-1];
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ch[0][0] = 1;
  for (int i = 1; i < maxn; i++) {
    ch[i][0] = 1;
    for (int j = 1; j <= min(2,i); j++) {
      ch[i][j] = ch[i-1][j-1] + ch[i-1][j];
    }
  }
  int t; cin >> t;
  while (t--) solve();
}

