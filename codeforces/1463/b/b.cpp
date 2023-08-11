#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    ll S = accumulate(a.begin(),a.end(),0LL);
    vector<ll> b1(n), b2(n);
    ll abs1 = 0, abs2 = 0;
    for (int i = 0; i < n; i++) {
      if (i%2==0) {
        b1[i] = 1;
        b2[i] = a[i];
      }
      else {
        b2[i] = 1;
        b1[i] = a[i];
      }
      abs1 += abs(b1[i]-a[i]);
      abs2 += abs(b2[i]-a[i]);
    }
    if (abs1 <= abs2) {
      for (auto i: b1) {
        cout << i << ' ';
      }
      cout << '\n';
    }
    else {
      for (auto i: b2) {
        cout << i << ' ';
      }
      cout << '\n';
    }
  }
}

