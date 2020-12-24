#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  int t; cin >> t;
  while (t--) {
    int x, y; cin >> x >> y;
    if (x < y) swap(x,y);
    cout << (x+y+max(0,x-y-1)) << '\n';
  }
}
