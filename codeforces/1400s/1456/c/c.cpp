#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) begin(x),end(x)

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  vector<ll> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(all(a),greater<ll>());
  if (k == 0) {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans += a[i]*(n-i-1);
    }
    cout << ans << '\n';
    return 0;
  }
  vector<ll> pos;
  for (int i = 0; i < n; i++) if (a[i] >= 0) pos.push_back(a[i]);
  vector<ll> neg;
  for (int i = 0; i < n; i++) if (a[i] < 0) neg.push_back(a[i]);
  ll X = 0;
  for (int i = 0; i < (int)pos.size(); i++) {
    X += ((int)pos.size()-i-1)*pos[i];
  }
  ll Y = accumulate(all(pos),0);

  ll Z = 0;
  vector<ll> negsum(neg.size());
  for (int i = 0; i < (int)neg.size(); i++) {
    negsum[i] = neg[i];
    if (i > 0) negsum[i] += negsum[i-1];
  }
  for (int i = 0; i < (int)neg.size(); i++) {
    Z += neg[i]*((int)neg.size()-i-1);
  }
  ll ans = X+Y*neg.size()+Z;
  int pt = neg.size()-1;
  int idx = 0;
  for (int i = 0; i < (int)neg.size(); i++) {

  }
}
