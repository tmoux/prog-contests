#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define all(x) begin(x),end(x)

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans = 0;
  for (int k = 0; k <= 24; k++) {
    vector<int> b;
    for (auto x: a) b.push_back(x % (1<<(k+1)));
    sort(all(b));
    ll cnt = 0;

    for (int i = 0; i < n; i++) {
      int x = b[i];
      int l = ((1<<(k+1)) + (1<<k) - x) % (1<<(k+1));
      int r = ((1<<(k+1)) - 1 - x) % (1<<(k+1));

      auto itl = lower_bound(b.begin()+i+1, b.end(), l);
      auto itr = upper_bound(b.begin()+i+1, b.end(), r);

      if (l <= r) {
        cnt += distance(itl, itr);
      }
      else {
        cnt += distance(itl, b.end());
        cnt += distance(b.begin()+i+1, itr);
      }
    }

    if (cnt&1) ans |= 1<<k;
  }
  cout << ans << '\n';
}
