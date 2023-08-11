#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int x; cin >> x;
    if (x > 45) {
      cout << -1 << '\n';
    }
    else {
      vector<int> v;
      for (int i = 9; i >= 1; i--) {
        if (x >= i) {
          v.push_back(i);
          x -= i;
        }
      }
      assert(x == 0);
      reverse(v.begin(),v.end());
      for (auto i:v) cout << i;
      cout << '\n';
    }
  }
}

