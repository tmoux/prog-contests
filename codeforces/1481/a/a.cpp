#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int x, y; cin >> x >> y;
    string s; cin >> s;
    int cx = 0, cy = 0;
    for (char c: s) {
      if (c == 'L' && x < 0) cx++;
      else if (c == 'R' && x > 0) cx++;
      else if (c == 'U' && y > 0) cy++;
      else if (c == 'D' && y < 0) cy++;
    }
    cout << (abs(x) <= cx && abs(y) <= cy ? "YES" : "NO") << '\n';
  }
}
