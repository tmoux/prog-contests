#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int n; cin >> n;
    deque<int> b(n);
    for (int i = 0; i < n; i++) {
      cin >> b[i];
    }
    while (!b.empty()) {
      int f = b.front();
      b.pop_front();
      cout << f << ' ';
      if (!b.empty()) {
        int c = b.back();
        b.pop_back();
        cout << c << ' ';
      }
    }
    cout << '\n';
  }
}
