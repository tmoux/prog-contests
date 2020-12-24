#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int x; cin >> x;
    int c = 0;
    int i = 1;
    while (c < x) {
      c += i;
      i++;
    }
    while (c+i <= x) {
      c += i;
      i++;
    }
    //cout << c << ' ' << x << ' ' << i << endl;
    if (x == c-1) i++;
    cout << i-1 << '\n';
  }
}
