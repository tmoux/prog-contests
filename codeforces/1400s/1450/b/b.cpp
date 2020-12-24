#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n, k; cin >> n >> k;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
      cin >> x[i] >> y[i];
    }
    bool poss = false;
    for (int i = 0; i < n; i++) {
      bool flag = true;
      for (int j = 0; j < n; j++) {
        if (abs(x[i]-x[j]) + abs(y[i]-y[j]) <= k) {

        }
        else {
          flag = false;
          break;
        }
      }
      if (flag) poss = true;
    }
    cout << (poss?1:-1) << '\n';
  }
}
