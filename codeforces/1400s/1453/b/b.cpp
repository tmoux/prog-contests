#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<ll> a(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (i > 0) {
        ans += abs(a[i]-a[i-1]);
      }
    }
    ll mx = 0;
    for (int i = 1; i < n-1; i++) {
      mx = max(mx,abs(a[i-1]-a[i])+abs(a[i]-a[i+1])-abs(a[i-1]-a[i+1]));
    }
    mx = max(mx,abs(a[0]-a[1]));
    mx = max(mx,abs(a.back()-a[a.size()-2]));
    //cout << "mx = " << mx << endl;
    cout << ans-mx << '\n';
  }
}
