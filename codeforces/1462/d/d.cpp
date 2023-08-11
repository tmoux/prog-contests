#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    vector<int> a(n);
    int tot = 0;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      tot += a[i];
    }
    for (int i = n; i >= 1; i--) {
      if (tot % i == 0) {
        int target = tot/i;
        bool poss = true;
        int cur = 0;
        for (int j = 0; j < n; j++) {
          if (cur+a[j] == target) {
            cur = 0;
          }
          else if (cur+a[j] < target) {
            cur += a[j];
          }
          else {
            poss = false;
          }
        }
        if (cur != 0) poss = false;
        if (poss) {
          cout << n-i << '\n';
          break;
        }
      }
    }
  }
}

