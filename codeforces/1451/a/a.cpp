#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    auto f = [](int n) {
      if (n == 1) return 0;
      else if (n == 2) return 1;
      else if (n % 2 == 0 || n == 3) return 2;
      else return 3;
    };
    cout << f(n) << '\n';
  }
}

