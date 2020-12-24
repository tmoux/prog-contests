#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll ceil(ll a, ll b) {
  return (a+b-1)/b;
}
int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  ll k, l, r, t, x, y;
  cin >> k >> l >> r >> t >> x >> y;
  k -= l;
  r -= l;
  //cout << x << ' ' << y << endl;
  if (x > y) {
    ll target = max(0LL,r-y);
    ll cnt = max(0LL,(k-target)/x);
    k -= cnt*x;
    assert(k >= 0);
    if (k+y <= r) {
      cnt += k/(x-y);
    }
    else if (k-x >= 0 && k-x+y <= r) {
      cnt++;
      k -= x;
      cnt += k/(x-y);
    }
    cout << (cnt>=t?"Yes":"No") << '\n';
    //cout << "cnt = " << cnt << endl;
    return 0;
  }
  set<ll> seen;
  ll cnt = 0;
  while (true) {
    if (k >= x) {
      cnt += k/x;
      k %= x;
    }
    if (cnt >= t) {
      cout << "Yes\n";
      return 0;
    }
    if (seen.count(k)) {
      cout << "Yes\n";
      return 0;
    }
    else {
      if (k+y > r || k+y-x < 0) {
        cout << (cnt>=t?"Yes":"No") << '\n';
        return 0;
      }
      else {
        seen.insert(k);
        k += y-x;
        cnt++;
      }
    }
  }
}
