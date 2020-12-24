#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, p, k; cin >> n >> p >> k;
    string s; cin >> s;
    vector<bool> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = s[i] == '1';
    }
    int x, y; cin >> x >> y;
    vector<int> cost(n);
    for (int i = n-1; i >= 0; i--) {
      if (i+k >= n) {
        cost[i] = !a[i];
      }
      else cost[i] = cost[i+k] + (!a[i]);
    }
    /*
    for (int i = 0; i < n; i++) {
      cout << cost[i] << ' ';
    }
    cout << '\n';
    */
    ll ans = 1e18;
    int before = 0;
    int open = 0;
    for (int i = p-1; i < n; i++) {
      ll tr = 1LL*cost[i]*x;
      tr += 1LL*(i-(p-1))*y;

      //cout << i << ": " << tr << '\n';
      ans = min(ans,tr);
      if (a[i]) before++;
      else open++;
    }
    cout << ans << '\n';
  }
}
