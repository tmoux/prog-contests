#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    ll n; cin >> n;
    map<ll,int> mp;
    ll c = n;
    for (ll i = 2; i*i <= n; i++) {
      while (c % i == 0) {
        mp[i]++;
        c /= i;
      }
    }
    if (c > 1) mp[c]++;

    pair<int,int> mx = {-1,-1};
    for (auto p: mp) {
      //cout << p.first << ": " << p.second << endl;
      mx = max(mx,{p.second,p.first});
    }
    int k = mx.first;
    cout << k << '\n';
    for (int i = 0; i < k-1; i++) {
      cout << mx.second << ' ';
      n /= mx.second;
    }
    cout << n << '\n';
  }
}
