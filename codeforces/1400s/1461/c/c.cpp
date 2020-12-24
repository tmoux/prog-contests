#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  cout << fixed << setprecision(10);
  while (t--) {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      --a[i];
    }
    int idx = n-1;
    while (idx >= 0 && a[idx] == idx) {
      idx--;
    }
    double ans = 1.0;
    while (m--) {
      int r;
      double p;
      cin >> r >> p;
      if (r > idx) {
        ans *= 1-p;
      }
    }
    if (idx == -1) {
      cout << 1.0 << '\n';
    }
    else {
      cout << (1-ans) << '\n';
    }
  }
}
