#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) ((int)x.size())

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    auto is_sorted = [](vector<int>& a) {
      for (int i = 1; i < sz(a); i++) {
        if (a[i] < a[i-1]) return false;
      }
      return true;
    };
    int ans = 0;
    for (int i = 0; i < sz(a); i++) {
      if (is_sorted(a)) break;
      if (a[i] > x) {
        swap(a[i],x);
        ans++;
      }
    }
    cout << (is_sorted(a)?ans:-1) << '\n';
  }
}
