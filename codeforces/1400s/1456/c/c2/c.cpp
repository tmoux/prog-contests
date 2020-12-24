#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int n, k; cin >> n >> k;
  priority_queue<ll> pq;
  for (int i = 0; i < k+1; i++) pq.push(0);
  vector<ll> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(),a.end(),greater<ll>());
  ll ans = 0;
  for (auto ai: a) {
    ll x = pq.top(); pq.pop();
    ans += x;
    pq.push(x+ai);
  }
  cout << ans << '\n';
}
