#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define x first
#define y second

pair<ll,ll> v[4];

ll try_perm(vector<int> u) {
  vector<pair<ll,ll>> p = 
    {v[u[0]],v[u[1]],v[u[2]],v[u[3]]};
  ll x1 = abs(p[0].x-p[1].x);
  ll x2 = abs(p[2].x-p[3].x);
  ll min_x = min(p[2].x,p[3].x)-max(p[0].x,p[1].x);
  ll max_x = max(p[2].x,p[3].x)-min(p[0].x,p[1].x);

  ll y1 = abs(p[0].y-p[2].y);
  ll y2 = abs(p[1].y-p[3].y);
  ll min_y = min(p[1].y,p[3].y)-max(p[0].y,p[2].y);
  ll max_y = max(p[1].y,p[3].y)-min(p[0].y,p[2].y);
  
  ll add = 0;
  pair<ll,ll> v1 = {min_x,max_x};
  pair<ll,ll> v2 = {min_y,max_y};
  if (v1.x > v2.x) swap(v1,v2);
  if (v1.y < v2.x) add = 2*(v2.x-v1.y);

  ll ans = x1 + x2 + y1 + y2 + add;
  return ans;
}

void solve() {
  for (int i = 0; i < 4; i++) {
    cin >> v[i].x >> v[i].y;
  }
  vector<int> p = {0,1,2,3};
  ll ans = 1e18;
  do {
    ans = min(ans,try_perm(p));
  } while (next_permutation(p.begin(),p.end()));
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) solve();
}
