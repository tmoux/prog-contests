#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    ll pos = 0;
    auto calc = [](ll x_init, ll x_end, ll t_init, ll t_cur) {
      ll t = t_cur-t_init;
      if (t < abs(x_init-x_end)) {
        if (x_init < x_end) return x_init + t;
        else return x_init - t;
      }
      return x_end;
    };
    vector<pair<ll,ll>> v;
    for (int i = 0; i < n; i++) {
      ll t, x; cin >> t >> x;
      v.push_back({t,x});
    }
    ll x_init = 0, x_end = 0, t_init = 0;

    int ans = 0;
    for (int i = 0; i < n; i++) {
      //cout << i << ": " << x_init << ' ' << x_end << ' ' << t_init << " :: " << calc(x_init,x_end,t_init,t) << '\n';
      ll t = v[i].first;
      ll x = v[i].second;
      if (calc(x_init,x_end,t_init,t) == x_end) {
        x_init = x_end;
        x_end = x;
        t_init = t;
      }
      ll t_next = i==n-1?1e15:v[i+1].first;
      ll now = calc(x_init,x_end,t_init,t);
      ll then = calc(x_init,x_end,t_init,t_next);
      if (min(now,then) <= x && x <= max(now,then)) {
        ans++;
      }
    }
    cout << ans << '\n';
  }
}
