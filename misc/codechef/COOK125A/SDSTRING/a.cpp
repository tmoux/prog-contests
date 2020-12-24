#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    string s; cin >> s;
    int n = s.size();
    int a = 0, b = 0;
    for (char c: s) {
      if (c == '0') a++;
      else b++;
    }
    if (n % 2 == 1) {
      cout << -1 << '\n';
    }
    else {
      if (a == 0 || b == 0) {
        cout << -1 << '\n';
      }
      else cout << abs(a-n/2) << '\n';
    }
  }
}

