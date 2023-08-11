#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, k; cin >> n >> k;
    vector<int> h(n);
    for (auto& i: h) cin >> i;
    auto pos = [n,&h]() {
      for (int i = 0; i < n-1; i++) {
        if (h[i] < h[i+1]) {
          h[i]++;
          return i+1;
        }
      }
      return -1;
    };
    for (int i = 0; i < k-1; i++) {
      int r = pos();
      if (r == -1) {
        cout << -1 << '\n';
        goto done;
      }
    }
    cout << pos() << '\n';
    done:;
  }
}
