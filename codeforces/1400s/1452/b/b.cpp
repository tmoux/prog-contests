#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& i: a) cin >> i;
    sort(a.begin(),a.end());
    ll sum = accumulate(a.begin(),a.end(),0LL);
    ll mx = a[n-1];
    ll k = max((sum+n-2)/(n-1),mx);
    ll tot = k*(n-1)-sum;
    cout << tot << '\n';
  }
}

